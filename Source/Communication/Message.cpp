// Copyright 2017 Frank Mueller
#include <vector>
#include "Message.h"

namespace BobOnRails {
namespace Firmware {
namespace Communication {

Message::Message() {
}

Message::Message(std::vector<int8_t> body) {
    this->body = body;
}

std::vector<int8_t> Message::getBody() {
    return body;
}

void Message::setBody(std::vector<int8_t> body) {
    this->body = body;
}
}       // namespace Communication
}       // namespace Firmware
}       // namespace BobOnRails
