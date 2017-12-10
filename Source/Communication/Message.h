// Copyright 2017 Frank Mueller
#ifndef SOURCE_COMMUNICATION_MESSAGE_H_
#define SOURCE_COMMUNICATION_MESSAGE_H_

#include <stdint.h>
#include <vector>

namespace BobOnRails {
namespace Firmware {
namespace Communication {

template<typename TMessageType>
class Message {
    public:
    Message() {
        this->type = static_cast<TMessageType>(0);
        this->body = std::vector<int8_t>(0);
    }

    explicit Message(TMessageType type, std::vector<int8_t> body) {
        this->type = type;
        this->body = body;
    }

    TMessageType getType() {
        return type;
    }

    void setType(TMessageType type) {
        this->type = type;
    }

    std::vector<int8_t> getBody() {
        return body;
    }

    void setBody(std::vector<int8_t> body) {
        this->body = body;
    }

    private:
    /** The message body. */
    std::vector<int8_t> body;

    TMessageType type;
};
}       // namespace Communication
}       // namespace Firmware
}       // namespace BobOnRails
#endif  // SOURCE_COMMUNICATION_MESSAGE_H_
