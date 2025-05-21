#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "TCPsocket.h"
#pragma comment (lib, "Ws2_32.lib")

using C_V = std::condition_variable;

struct massag {
    int id;
    int size;
    char* buff;
};


class signalTCPthread {
    C_V cvFromNet, cvToNet, cvRun;
    std::mutex mutFromNet, mutToNet, mutRun;
    bool bFromNet = false, bToNet = false, bRun = false;
public:
    
    bool forFromNet() {return bFromNet; }
    bool forToNet() { return bToNet; }
    bool forRun() { return bRun; }

    friend void runTCPthread(int, massag&,signalTCPthread&);
    friend class TCPserver;
};


void runTCPthread(int clientSock, massag& mass, signalTCPthread& signal) {
    while (true) {
        std::unique_lock<std::mutex> mut(signal.mutToNet);
        signal.cvToNet.wait(mut, [&]() {return signal.forToNet(); });
        signal.bToNet = false;
        send(clientSock, mass.buff, mass.size, 0);

        std::unique_lock<std::mutex> mut2(signal.mutRun);
        signal.cvRun.wait(mut, [&]() {return signal.forRun(); });
        if (signal.bRun)
            break;

        std::unique_lock<std::mutex> mut3(signal.mutFromNet);
        signal.bFromNet = true;
        size_t sz = recv(clientSock, mass.buff, mass.size, 0);
        signal.cvFromNet.notify_one();

    }
}


class TCPserver {
    TCPsocket listenSock;
    std::thread listenThrd;
    //std::vector<TCPsocket> vecSock;
    std::vector<std::thread> vecThread;
    //std::vector<C_V> vecCV;
    //C_V cvFromNet, cvToNet, cvRun;
    std::vector<int> vecNumberClient;
    signalTCPthread signalThrd;
    std::string addr;
    int port;
    massag massg;
public:
    TCPserver(std::string _addr, int _port): addr(_addr), port(_port), listenSock(addr,port){
        listenThrd = std::thread(run);
    }

    int countClient() { return vecNumberClient.size(); }

    void run() {
        int haveNew = listenSock.TCPlisten( 20);

        while (true) {
            int newClientSock = listenSock.TCPaccept();
            vecNumberClient.push_back(newClientSock);
            vecThread.push_back(std::thread(runTCPthread, newClientSock, std::ref(massg), std::ref(signalThrd)));
        }
    }

    void stop() {
        std::unique_lock<std::mutex> mut(signalThrd.mutRun);
        signalThrd.bRun = true;
        signalThrd.cvRun.notify_one();
    }

    void send(int numClient, massag& mass) {
        int tempSock;
        if (numClient <= vecNumberClient.size() && numClient > 0)
            tempSock = vecNumberClient[numClient - 1];
        else return;
        std::unique_lock<std::mutex> mut(signalThrd.mutToNet);
        signalThrd.bToNet = true;
        mass.id = numClient;        
        signalThrd.cvRun.notify_one();
    }
};



