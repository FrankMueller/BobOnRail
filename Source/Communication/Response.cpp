// Copyright 2017 Frank Mueller
#include <vector>
#include "Response.h"

namespace BobOnRails {
namespace Firmware {
namespace Communication {

Response::Response() {
}

Response::Response(ResponseTypes type, std::vector<int8_t> body) : Message(body) {
    this->type = type;
}

void Response::setType(ResponseTypes type) {
    this->type = type;
}

ResponseTypes Response::getType() {
    return type;
}

void Response::setTypeCode(int8_t code) {
    type = static_cast<ResponseTypes>(code);
}

int8_t Response::getTypeCode() {
    return static_cast<int8_t>(type);
}

}       // namespace Communication
}       // namespace Firmware
}       // namespace BobOnRails
