// Copyright 2017 Frank Mueller
#ifndef SOURCE_GYROSENSOR_H_
#define SOURCE_GYROSENSOR_H_

#include "Vector3.h"

namespace BobOnRails {
namespace Firmware {

class GyroSensor {
 public:
    const float gToMeterPerSecond = 9.81f;

    /**
       Establishes a connection to the device.

       @return zero if the operation succeeded; otherwise an error code.
     */
    virtual int connect() = 0;

    /**
       Reads the current measurement data from the device.

       @param[out]  acceleration The measured acceleration in m/s^2
       @param[out]  gyration The measured gyration in deg/s^2
       @param[out]  temperature The measured temperature in °C

       @return zero if the operation succeeded; otherwise an error code.
     */
    virtual int measure(Vector3* acceleration, Vector3* gyration, float* temperature) = 0;
};
}       // namespace Firmware
}       // namespace BobOnRails
#endif  // SOURCE_GYROSENSOR_H_
