// Copyright 2017 Frank Mueller
#ifndef SOURCE_COMMUNICATION_REQUESTTYPES_H_
#define SOURCE_COMMUNICATION_REQUESTTYPES_H_

namespace BobOnRails {
namespace Firmware {
namespace Communication {

enum class RequestTypes {
    /** Request to reply with the same data that was send (esp. for test purposes). */
    Echo = 0,
    /** Request to perform the disconnect logic. */
    Disconnect = 1,
    /** Request to start sending accelerometer measurement data. */
    StartAccelerometerDataStream = 2,
    /** Request to stop sending accelerometer measurement data. */
    StopAccelerometerDataStream = 3
};
}       // namespace Communication
}       // namespace Firmware
}       // namespace BobOnRails
#endif  // SOURCE_COMMUNICATION_REQUESTTYPES_H_
