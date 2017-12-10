// Copyright 2017 Frank Mueller
#ifndef SOURCE_COMMUNICATION_RESPONSE_H_
#define SOURCE_COMMUNICATION_RESPONSE_H_

#include <vector>
#include "Message.h"
#include "ResponseTypes.h"

namespace BobOnRails {
namespace Firmware {
namespace Communication {

class Response : public Message {
    public:
    Response();

    Response(ResponseTypes type, std::vector<int8_t> body);

    virtual int8_t getTypeCode();

    virtual void setTypeCode(int8_t code);

    ResponseTypes getType();

    void setType(ResponseTypes type);

    private:
    ResponseTypes type;
};
}       // namespace Communication
}       // namespace Firmware
}       // namespace BobOnRails
#endif  // SOURCE_COMMUNICATION_RESPONSE_H_
