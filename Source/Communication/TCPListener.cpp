// Copyright 2017 Frank Mueller
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <cstring>
#include "TCPListener.h"

namespace BobOnRails {
namespace Firmware {
namespace Communication {

TCPClient<RequestTypes, ResponseTypes> TCPListener::listen(const uint16_t port) {
    auto socketId = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddr;
    std::memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    int error = 0;
    if (bind(socketId, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) != 0) {
        close(socketId);
        error = errno;
    }

    if (::listen(socketId, 1) != 0) {
        close(socketId);
        error = errno;
    }

    sockaddr_storage serverStorage;
    socklen_t addr_size = sizeof serverStorage;
    auto clientSocketId = accept(socketId, (struct sockaddr*)&serverStorage, &addr_size);
    if (clientSocketId < 0) {
        error = errno;
    }

    close(socketId);

    TCPClient<RequestTypes, ResponseTypes> client(clientSocketId);
    return client;
}

}       // namespace Communication
}       // namespace Firmware
}       // namespace BobOnRails
