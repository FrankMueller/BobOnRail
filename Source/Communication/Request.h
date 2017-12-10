// Copyright 2017 Frank Mueller
#ifndef SOURCE_COMMUNICATION_REQUEST_H_
#define SOURCE_COMMUNICATION_REQUEST_H_

#include <vector>
#include "Message.h"
#include "RequestTypes.h"

namespace BobOnRails {
namespace Firmware {
namespace Communication {

class Request : public Message {
    public:
    Request();

    Request(RequestTypes type, std::vector<int8_t> body);

    virtual int8_t getTypeCode();

    virtual void setTypeCode(int8_t code);

    RequestTypes getType();

    void setType(RequestTypes type);

    private:
    RequestTypes type;
};
}       // namespace Communication
}       // namespace Firmware
}       // namespace BobOnRails
#endif  // SOURCE_COMMUNICATION_REQUEST_H_
