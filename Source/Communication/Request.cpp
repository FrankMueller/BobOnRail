// Copyright 2017 Frank Mueller
#include <vector>
#include "Request.h"

namespace BobOnRails {
namespace Firmware {
namespace Communication {

Request::Request() {
}

Request::Request(RequestTypes type, std::vector<int8_t> body) : Message(body) {
    this->type = type;
}

void Request::setType(RequestTypes type) {
    this->type = type;
}

RequestTypes Request::getType() {
    return type;
}

void Request::setTypeCode(int8_t code) {
    type = static_cast<RequestTypes>(code);
}

int8_t Request::getTypeCode() {
    return static_cast<int8_t>(type);
}

}       // namespace Communication
}       // namespace Firmware
}       // namespace BobOnRails
