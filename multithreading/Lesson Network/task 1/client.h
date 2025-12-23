#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>
#pragma comment (lib, "Ws2_32.lib")

class TCPclient {
    int descriptSock;
    sockaddr_in addres{};
    
public:
    TCPclient(std::string addr, int port) {
        descriptSock = socket(AF_INET6, SOCK_STREAM, 0);
        addres.sin_family = AF_INET6;
        addres.sin_addr.s_addr = inet_addr(addr.c_str());
        addres.sin_port = htons(port);
        int f = connect(descriptSock, (sockaddr*) & addres, sizeof(addres));

    }
    ~TCPclient() {
        closesocket(descriptSock);
    }

    void TCPsend(const char* buff, size_t size) {
        send(descriptSock, buff, size, 0);
    }
    size_t TCPrecv(char* buff, size_t size) {
        size_t sz = recv(descriptSock, buff, size, 0);
        return sz;
    }
};
