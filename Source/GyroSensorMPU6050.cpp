// Copyright 2017 Frank Mueller
#include "GyroSensorMPU6050.h"
#include "GyroSensorMPU6050Constants.h"
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <limits>

namespace BobOnRails {
namespace Firmware {

GyroSensorMPU6050::GyroSensorMPU6050() {
    deviceHandle = 0;
}

GyroSensorMPU6050::~GyroSensorMPU6050() {
    if (deviceHandle != 0)
        close(deviceHandle);
}

int GyroSensorMPU6050::connect() {
    // Initialize the I2C-bus.
    auto *deviceName = const_cast<char*>("/dev/i2c-1");
    deviceHandle = open(deviceName, O_RDWR);
    if (deviceHandle < 0) {
        printf("Error while connecting to device %s\n", deviceName);
        return deviceHandle;
    }

    auto error = ioctl(deviceHandle, I2C_SLAVE, MPU6050_I2C_ADDRESS);
    if (error != 0) {
        printf("Error while establishing communication (error code %d)\n", error);
        return error;
    }

    // default at power-up:
    //    Gyro at 250 degrees second
    //    Acceleration at 2g
    //    Clock source at internal 8MHz
    //    The device is in sleep mode.
    uint8_t deviceInfo;
    error = readFromMPU6050(MPU6050_WHO_AM_I, &deviceInfo, 1);
    if (error != 0)
        printf("Device info: error (code %d)\n", error);
    else
        printf("Device info: %d\n", deviceInfo);

    // According to the datasheet, the 'sleep' bit
    // should read a '1'.
    // That bit has to be cleared, since the sensor
    // is in sleep mode at power-up.
    uint8_t powerMode;
    error = readFromMPU6050(MPU6050_PWR_MGMT_1, &powerMode, 1);
    if (error != 0)
        printf("Initial power mode: error (code %d)\n", error);
    else
        printf("Initial power mode: %d\n", powerMode);

    // Clear the 'sleep' bit to start the sensor.
    if (powerMode != 0) {
        printf("Sending wake up signal...");
        error = writeToMPU6050(MPU6050_PWR_MGMT_1, 0);
        if (error != 0)
            printf("error (code %d)\n", error);
        else
            printf("done\n");
    }

    GyroResolutions gyroResolution;
    if (getGyrationResolution(&gyroResolution) == 0)
        gyrationGain = static_cast<float>(gyroResolution) / std::numeric_limits<int16_t>::max();
    else
        gyrationGain = 1.0;

    AccelerationResolutions accelerationResolution;
    if (getAccelerationResolution(&accelerationResolution) == 0)
        accelerationGain = static_cast<float>(accelerationResolution) / std::numeric_limits<int16_t>::max();
    else
        accelerationGain = 1.0;

    accelerationGain *= gToMeterPerSecond;

    temperatureOffset = 12412.0;
    temperatureGain = 1.0f / 340.0f;

    return error;
}

int GyroSensorMPU6050::measure(Vector3* acceleration, Vector3* gyration, float* temperature) {
    // Read the raw values.
    MPU6050RawData rawData;
    auto error = readFromMPU6050(MPU6050_ACCEL_XOUT_H, reinterpret_cast<uint8_t *>(&rawData), sizeof(rawData));
    if (error != 0) {
        printf("Error while reading measurement data (code %d)\n", error);
        return error;
    }

    acceleration->X = decodeRawValue(rawData.acceleration_x_high, rawData.acceleration_x_low) * accelerationGain;
    acceleration->Y = decodeRawValue(rawData.acceleration_y_high, rawData.acceleration_y_low) * accelerationGain;
    acceleration->Z = decodeRawValue(rawData.acceleration_z_high, rawData.acceleration_z_low) * accelerationGain;

    gyration->X = decodeRawValue(rawData.gyration_x_high, rawData.gyration_x_low) * gyrationGain;
    gyration->Y = decodeRawValue(rawData.gyration_y_high, rawData.gyration_y_low) * gyrationGain;
    gyration->Z = decodeRawValue(rawData.gyration_z_high, rawData.gyration_z_low) * gyrationGain;

    // The temperature sensor is -40 to +85 degrees Celsius.
    // It is a signed integer.
    // According to the datasheet:
    //   340 per degrees Celsius, -512 at 35 degrees.
    // At 0 degrees: -512 - (340 * 35) = -12412
    auto temperatureValue = decodeRawValue(rawData.temperature_high, rawData.temperature_low);
    *temperature = (temperatureValue + temperatureOffset) * temperatureGain;

    return 0;
}

int GyroSensorMPU6050::getGyrationResolution(GyroResolutions* resolution) {
    printf("Getting gyro resolution...");

    uint8_t resolutionFlag;
    auto error = readFromMPU6050(MPU6050_FS_SEL0, &resolutionFlag, 1);
    if (error != 0) {
        printf("error (code %d)\n", error);
    } else {
        if ((resolutionFlag & MPU6050_FS_SEL_2000) == MPU6050_FS_SEL_2000) {
            *resolution = GyroResolutions::GyroLow;
        } else if ((resolutionFlag & MPU6050_FS_SEL_1000) == MPU6050_FS_SEL_1000) {
            *resolution = GyroResolutions::GyroMedium;
        } else if ((resolutionFlag & MPU6050_FS_SEL_500) == MPU6050_FS_SEL_500) {
            *resolution = GyroResolutions::GyroHigh;
        } else if ((resolutionFlag & MPU6050_FS_SEL_250) == MPU6050_FS_SEL_250) {
            *resolution = GyroResolutions::GyroVeryHigh;
        } else {
            printf("error (Unknown resolution set on device:%d)\n", resolutionFlag);
            return -1;
        }

        printf("%d °/s\n", *resolution);
    }

    return error;
}

int GyroSensorMPU6050::setGyrationResolution(GyroResolutions resolution) {
    printf("Setting gyro resolution to %d °/s...", resolution);

    uint8_t resolutionFlag;
    if (resolution == GyroResolutions::GyroLow) {
        resolutionFlag = MPU6050_FS_SEL_2000;
    } else if (resolution == GyroResolutions::GyroMedium) {
        resolutionFlag = MPU6050_FS_SEL_1000;
    } else if (resolution == GyroResolutions::GyroHigh) {
        resolutionFlag = MPU6050_FS_SEL_500;
    } else if (resolution == GyroResolutions::GyroVeryHigh) {
        resolutionFlag = MPU6050_FS_SEL_250;
    } else {
        printf("error (The specified resolution is not supported!)\n");
        return -1;
    }

    int error = writeToMPU6050(MPU6050_FS_SEL0, resolutionFlag);
    if (error != 0) {
        printf("error (code %d)\n", error);
    } else {
        gyrationGain = static_cast<float>(resolution) / std::numeric_limits<int16_t>::max();
        printf("done\n");
    }

    return error;
}

int GyroSensorMPU6050::getAccelerationResolution(AccelerationResolutions* resolution) {
    printf("Getting acceleration resolution...");

    uint8_t resolutionFlag;
    int error = readFromMPU6050(MPU6050_AFS_SEL0, &resolutionFlag, 1);
    if (error != 0) {
        printf("error (code %d)\n", error);
    } else {
        if ((resolutionFlag & MPU6050_AFS_SEL_16G) == MPU6050_AFS_SEL_16G) {
            *resolution = AccelerationResolutions::AccLow;
        } else if ((resolutionFlag & MPU6050_AFS_SEL_8G) == MPU6050_AFS_SEL_8G) {
            *resolution = AccelerationResolutions::AccMedium;
        } else if ((resolutionFlag & MPU6050_AFS_SEL_4G) == MPU6050_AFS_SEL_4G) {
            *resolution = AccelerationResolutions::AccHigh;
        } else if ((resolutionFlag & MPU6050_AFS_SEL_2G) == MPU6050_AFS_SEL_2G) {
            *resolution = AccelerationResolutions::AccVeryHigh;
        } else {
            printf("error (Unknown resolution set on device: %d)\n", resolutionFlag);
            return -1;
        }

        printf("%d g\n", *resolution);
    }

    return error;
}

int GyroSensorMPU6050::setAccelerationResolution(AccelerationResolutions resolution) {
    printf("Setting acceleration resolution to %d g...", resolution);

    uint8_t resolutionFlag;
    if (resolution == AccelerationResolutions::AccLow) {
        resolutionFlag = MPU6050_AFS_SEL_16G;
    } else if (resolution == AccelerationResolutions::AccMedium) {
        resolutionFlag = MPU6050_AFS_SEL_8G;
    } else if (resolution == AccelerationResolutions::AccHigh) {
        resolutionFlag = MPU6050_AFS_SEL_4G;
    } else if (resolution == AccelerationResolutions::AccVeryHigh) {
        resolutionFlag = MPU6050_AFS_SEL_2G;
    } else {
        printf("error (The specified resolution is not supported!)\n");
        return -1;
    }

    int error = writeToMPU6050(MPU6050_AFS_SEL0, resolutionFlag);
    if (error != 0) {
        printf("error (code %d)\n", error);
    } else {
        accelerationGain = gToMeterPerSecond * static_cast<float>(resolution) / std::numeric_limits<int16_t>::max();
        printf("done\n");
    }

    return error;
}

int GyroSensorMPU6050::readFromMPU6050(uint8_t command, uint8_t* buffer, uint8_t size) {
    int result = i2c_smbus_read_i2c_block_data(deviceHandle, command, size, buffer);
    if (result != size) {
        printf("Error while reading from device.");
        return -1;
    }
    return 0;
}

int GyroSensorMPU6050::writeToMPU6050(uint8_t command, uint8_t value) {
    int result = i2c_smbus_write_byte_data(deviceHandle, command, value);
    if (result < 0) {
        printf("Error while writing to device.");
        return result;
    }
    return 0;
}

float GyroSensorMPU6050::decodeRawValue(uint8_t msb, uint8_t lsb) {
    auto combined = (int16_t)(msb << 8) | (lsb & 0xFF);

    return static_cast<float>(combined);
}
}       // namespace Firmware
}       // namespace BobOnRails
