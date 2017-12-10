// Copyright 2017 Frank Mueller
#ifndef SOURCE_COMMUNICATION_TCPCLIENT_H_
#define SOURCE_COMMUNICATION_TCPCLIENT_H_

#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include "Response.h"

namespace BobOnRails {
namespace Firmware {
namespace Communication {

template<typename TIncomingMessage, typename TOutgoingMessage>
class TCPClient {
    public:
    explicit TCPClient(const int socketId) {
        this->socketId = socketId;

        // setup the file descriptor to check for incoming data
        incomingDataCheckTimeout.tv_sec = 0;
        incomingDataCheckTimeout.tv_usec = 50;
    }

    bool messageAvailable() {
        // check if there is data available
        fd_set incomingStreamDescriptor;
        FD_ZERO(&incomingStreamDescriptor);
        FD_SET(socketId, &incomingStreamDescriptor);
        auto availableDescriptorCount = select(socketId + 1, &incomingStreamDescriptor, NULL, NULL, &incomingDataCheckTimeout);

        return availableDescriptorCount == 1;
    }

    int sendMessage(TOutgoingMessage message) {
        size_t bytesSend;

        //Send the message type
        int8_t messageType = message.getTypeCode();
        bytesSend = send(socketId, &messageType, sizeof(messageType), 0);
        if (bytesSend < 0)
            return errno;

        //Send the message body size
        size_t bodySize = message.getBody().size();
        bytesSend = send(socketId, &bodySize, sizeof(bodySize), 0);
        if (bytesSend < 0)
            return errno;

        //Send the message body
        auto body = message.getBody().data();
        size_t bodyBytesSend = 0;
        while (bodyBytesSend < bodySize) {
            bytesSend = send(socketId, body + bodyBytesSend, bodySize - bodyBytesSend, 0);
            if (bytesSend < 0)
                return errno;

            bodyBytesSend += bytesSend;
        }

        return 0;
    }

    int receiveMessage(TIncomingMessage *message) {
        size_t bytesRead;

        //Read the message type byte
        int8_t messageTypeCode;
        bytesRead = recv(socketId, &messageTypeCode, sizeof(messageTypeCode), 0);
        if (bytesRead < 0)
            return errno;

        //Read the message body length
        size_t bodyLength;
        bytesRead = recv(socketId, &bodyLength, sizeof(bodyLength), 0);
        if (bytesRead < 0)
            return errno;

        //Read the message body
        std::vector<int8_t> messageBody(bodyLength);
        auto buffer = messageBody.data();
        size_t bodyBytesRead = 0;
        while (bodyBytesRead < bodyLength) {
            // The inner loop handles interactions with the socket.
            bytesRead = recv(socketId, buffer + bodyBytesRead, bodyLength - bodyBytesRead, 0);
            if (bytesRead < 0)
                return errno;
            else if (bytesRead == 0)
                return -1;

            bodyBytesRead += bytesRead;
        }

        message->setTypeCode(messageTypeCode);
        message->setBody(messageBody);

        return 0;
    }

    int shutdown() {
        auto error = shutdown(socketId(), SHUT_RDWR);
        if (error != 0)
            return errno;

        return 0;
    }

    private:
    int socketId;
    timeval incomingDataCheckTimeout;
};
}       // namespace Communication
}       // namespace Firmware
}       // namespace BobOnRails
#endif  // SOURCE_COMMUNICATION_TCPCLIENT_H_
