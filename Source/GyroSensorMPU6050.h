#ifndef BobOnRails_Firmware_GyroSensorMPU6050_H
#define BobOnRails_Firmware_GyroSensorMPU6050_H

#include <stdint.h>
#include "Vector3.h"
#include "GyroSensor.h"

namespace BobOnRails::Firmware {

    class GyroSensorMPU6050 {
        
        public:
            enum AccelerationResolutions { AccLow = 16, AccMedium = 8, AccHigh = 4, AccVeryHigh = 2 };

            enum GyroResolutions { GyroLow = 2000, GyroMedium = 1000, GyroHigh = 500, GyroVeryHigh = 250 };
    
            GyroSensorMPU6050();

	    ~GyroSensorMPU6050();

            int connect();
            
            int measure(Vector3* acceleration, Vector3* gyration, float* temperature);
            
            int getGyrationResolution(GyroResolutions* resolution);
            
            int setGyrationResolution(GyroResolutions resolution);
            
            int getAccelerationResolution(AccelerationResolutions* resolution);
            
            int setAccelerationResolution(AccelerationResolutions resolution);
    

        private:
            int deviceHandle;
            float temperatureOffset;
            float temperatureGain;
            float accelerationGain;
            float gyrationGain;
            
            int readFromMPU6050(uint8_t command, uint8_t* buffer, uint8_t size);
            
            int writeToMPU6050(uint8_t command, uint8_t value);
            
            struct MPU6050RawData {
                uint8_t acceleration_x_high;
                uint8_t acceleration_x_low;
                uint8_t acceleration_y_high;
                uint8_t acceleration_y_low;
                uint8_t acceleration_z_high;
                uint8_t acceleration_z_low;
                uint8_t temperature_high;
                uint8_t temperature_low;
                uint8_t gyration_x_high;
                uint8_t gyration_x_low;
                uint8_t gyration_y_high;
                uint8_t gyration_y_low;
                uint8_t gyration_z_high;
                uint8_t gyration_z_low;
            };
    };
}

#endif
