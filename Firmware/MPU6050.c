#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <stdio.h>
#include "MPU6050.h" 

// Declaring an union for the registers and the axis values.
// The byte order does not match the byte order of
// the compiler and AVR chip.
// The AVR chip (on the Arduino board) has the Low Byte
// at the lower address.
// But the MPU-6050 has a different order: High Byte at
// lower address, so that has to be corrected.
// The register part "reg" is only used internally,
// and are swapped in code.
typedef union accel_t_gyro_union
{
  struct
  {
    uint8_t x_accel_h;
    uint8_t x_accel_l;
    uint8_t y_accel_h;
    uint8_t y_accel_l;
    uint8_t z_accel_h;
    uint8_t z_accel_l;
    uint8_t t_h;
    uint8_t t_l;
    uint8_t x_gyro_h;
    uint8_t x_gyro_l;
    uint8_t y_gyro_h;
    uint8_t y_gyro_l;
    uint8_t z_gyro_h;
    uint8_t z_gyro_l;
  } reg;
  struct
  {
    int16_t x_accel;
    int16_t y_accel;
    int16_t z_accel;
    int16_t temperature;
    int16_t x_gyro;
    int16_t y_gyro;
    int16_t z_gyro;
  } value;
} Horst;
 
int deviceHandle; 

 
int readFromMPU6050(uint8_t command, uint8_t *buffer, uint8_t size)
{
    int result = i2c_smbus_read_i2c_block_data(deviceHandle, command, size, buffer);
    if (result != size)
    {
        printf("Error while reading from device.");
        return -1;
    } 
	return 0;
}
 
int writeToMPU6050(uint8_t command, uint8_t value)
{
    int result = i2c_smbus_write_byte_data(deviceHandle, command, value);
    if (result < 0)
    {
        printf("Error while writing to device.");
        return result;
    }
	return 0;
}

void connectMPU6050()
{      
    int error;
    uint8_t c;
 
    printf("InvenSense MPU-6050\n");
 
    //Initialize the I2C-bus.
    char *deviceName = (char*)"/dev/i2c-1";
    deviceHandle = open(deviceName, O_RDWR);
    if (deviceHandle < 0)
    {
        printf("Error while connecting to device %s\n", deviceName);
        return;
    }
    
    error = ioctl(deviceHandle, I2C_SLAVE, MPU6050_I2C_ADDRESS);
    if (error != 0)
    {
        printf("Error while establishing communication (error code %d)\n", error);
        return;
    }
 
    // default at power-up:
    //    Gyro at 250 degrees second
    //    Acceleration at 2g
    //    Clock source at internal 8MHz
    //    The device is in sleep mode.
    error = readFromMPU6050(MPU6050_WHO_AM_I, &c, 1);
    if (error != 0)
        printf("Device info: error (code %d)\n", error);
    else
        printf("Device info: %d\n", c);
   
    // According to the datasheet, the 'sleep' bit
    // should read a '1'.
    // That bit has to be cleared, since the sensor
    // is in sleep mode at power-up.
    error = readFromMPU6050(MPU6050_PWR_MGMT_1, &c, 1);
    if (error != 0)
        printf("Initial power mode: error (code %d)\n", error);
    else
        printf("Initial power mode: %d\n", c);
  
    // Clear the 'sleep' bit to start the sensor.
    if (c != 0)
    {
        printf("Sending wake up signal...");
        error = writeToMPU6050(MPU6050_PWR_MGMT_1, 0);
        if (error != 0)
            printf("error (code %d)\n", error);
        else
            printf("done\n");
    }
}
 
void test()
{
    int error;
    Horst accel_t_gyro;
        
    // Read the raw values.
    // Read 14 bytes at once,
    // containing acceleration, temperature and gyro.
    // With the default settings of the MPU-6050,
    // there is no filter enabled, and the values
    // are not very stable.
    error = readFromMPU6050(MPU6050_ACCEL_XOUT_H, (uint8_t *) &accel_t_gyro, sizeof(accel_t_gyro));
    if (error != 0)
    {
	    printf("Read accel, temp and gyro, error = %d\n", error);
	    return;
    }
    
    // Swap all high and low bytes.
    // After this, the registers values are swapped,
    // so the structure name like x_accel_l does no
    // longer contain the lower byte.
    uint8_t swap;
    #define SWAP(x,y) swap = x; x = y; y = swap
    
    SWAP (accel_t_gyro.reg.x_accel_h, accel_t_gyro.reg.x_accel_l);
    SWAP (accel_t_gyro.reg.y_accel_h, accel_t_gyro.reg.y_accel_l);
    SWAP (accel_t_gyro.reg.z_accel_h, accel_t_gyro.reg.z_accel_l);
    SWAP (accel_t_gyro.reg.t_h, accel_t_gyro.reg.t_l);
    SWAP (accel_t_gyro.reg.x_gyro_h, accel_t_gyro.reg.x_gyro_l);
    SWAP (accel_t_gyro.reg.y_gyro_h, accel_t_gyro.reg.y_gyro_l);
    SWAP (accel_t_gyro.reg.z_gyro_h, accel_t_gyro.reg.z_gyro_l);
    
    // Print the raw acceleration values
    printf("Acceleration x,y,z: %d, %d, %d\n", accel_t_gyro.value.x_accel, 
        accel_t_gyro.value.y_accel, accel_t_gyro.value.z_accel);
    
    // The temperature sensor is -40 to +85 degrees Celsius.
    // It is a signed integer.
    // According to the datasheet:
    //   340 per degrees Celsius, -512 at 35 degrees.
    // At 0 degrees: -512 - (340 * 35) = -12412
    double dT = ( (double) accel_t_gyro.value.temperature + 12412.0) / 340.0;
    printf("Temperature: %f [°]\n", dT);
    
    // Print the raw gyro values.
    printf("Gyro x,y,z: %d, %d, %d\n", accel_t_gyro.value.x_gyro,
        accel_t_gyro.value.y_gyro, accel_t_gyro.value.z_gyro);
}
