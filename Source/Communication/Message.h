// Copyright 2017 Frank Mueller
#ifndef SOURCE_COMMUNICATION_MESSAGE_H_
#define SOURCE_COMMUNICATION_MESSAGE_H_

#include <stdint.h>
#include <vector>

namespace BobOnRails {
namespace Firmware {
namespace Communication {

class Message {
 public:
    Message();

    explicit Message(std::vector<int8_t> body);

    virtual int8_t getTypeCode() = 0;

    virtual void setTypeCode(int8_t code) = 0;

    std::vector<int8_t> getBody();

    void setBody(std::vector<int8_t> body);
 
 private:
    /** The message body. */
    std::vector<int8_t> body;
};
}       // namespace Communication
}       // namespace Firmware
}       // namespace BobOnRails
#endif  // SOURCE_COMMUNICATION_MESSAGE_H_
