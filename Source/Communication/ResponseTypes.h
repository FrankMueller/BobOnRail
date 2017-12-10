// Copyright 2017 Frank Mueller
#ifndef SOURCE_COMMUNICATION_RESPONSETYPES_H_
#define SOURCE_COMMUNICATION_RESPONSETYPES_H_

namespace BobOnRails {
namespace Firmware {
namespace Communication {

enum class ResponseTypes {
    /** Response to a <see cref="RequestTypes::Echo"/> request (esp. for test purposes). */
    Echo = 0,
    /** Response telling that the diconnection logic was started on the device. */
    Disconnect = 1,
    /** Response containing an accelerometer measurement data set. */
    AccelerometerData = 2
};
}       // namespace Communication
}       // namespace Firmware
}       // namespace BobOnRails
#endif  // SOURCE_COMMUNICATION_RESPONSETYPES_H_
