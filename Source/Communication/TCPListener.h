// Copyright 2017 Frank Mueller
#ifndef SOURCE_COMMUNICATION_TCPLISTENER_H_
#define SOURCE_COMMUNICATION_TCPLISTENER_H_

#include "RequestTypes.h"
#include "ResponseTypes.h"
#include "TCPClient.h"

namespace BobOnRails {
namespace Firmware {
namespace Communication {

class TCPListener {
    public:
    static TCPClient<RequestTypes, ResponseTypes> listen(const uint16_t port);

    private:
    TCPListener();
};

}       // namespace Communication
}       // namespace Firmware
}       // namespace BobOnRails

#endif  // SOURCE_COMMUNICATION_TCPLISTENER_H_
