#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>
#include <iostream>
#pragma comment (lib, "Ws2_32.lib")

class TCPsocket {
    int descriptSock;
    sockaddr_in my_addr{}, client_addr{};

public:
    TCPsocket(std::string addr, int port) {
        descriptSock = socket(AF_INET6, SOCK_STREAM, 0);
        my_addr.sin_family = AF_INET6;
        my_addr.sin_addr.s_addr = INADDR_ANY;
        my_addr.sin_port = htons(port);
        int err = bind(descriptSock, (sockaddr*)&my_addr, sizeof(my_addr));
        if (err == SOCKET_ERROR) {
            std::cout << "Ошибка создания сокета";
            closesocket(descriptSock);
        }
    }
    ~TCPsocket() {
        closesocket(descriptSock);
    }

    int getDescriptor(){ return descriptSock; }

    void TCPsend(char* buff, size_t size) {
        send(descriptSock, buff, size, 0);
    }
    size_t TCPrecv(char* buff, size_t size) {
        size_t sz = recv(descriptSock, buff, size, 0);
        return sz;
    }

    int TCPlisten(int max) {
        
            int err = listen(descriptSock, max);
            return err;
    }

    int TCPaccept() {
        int sz = sizeof(client_addr);
        int newDescrClient = accept(descriptSock, (sockaddr*)&client_addr, &sz);
        std::cout << "Соединение установленно";
        return newDescrClient;
    }
    /*int TCPaccept(int descrSock) {
        int sz = sizeof(client_addr);
        int newDescrClient = accept(descrSock, (sockaddr*)&client_addr, &sz);
        std::cout << "Соединение установленно";
        return newDescrClient;
    }*/
};










