#include <iostream>
#include "TCPsocket.h"
#include "multithread server.h"



int main()
{
    setlocale(LC_ALL, "Russian");

    TCPserver server(std::string{ "107.0.0.1" }, 13000);
    char* m = new char[30];
    massag mass;
    mass.buff = m;
    mass.size = 30;

    if(server.countClient()==1)
        server.send(1, mass);
    server.stop();

    delete[] m;

    

}
