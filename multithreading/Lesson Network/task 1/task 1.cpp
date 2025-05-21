#include <iostream>
#include "client.h"

struct struc {
    int i = 3;
    char c = 'c';
};

int main()
{
    std::string ipServ("107.0.0.1");
    int portServ = 13000;
    TCPclient client(ipServ, portServ);
    std::string text{ "test text" };
    client.TCPsend(text.c_str(), text.size());

    struc data;
    client.TCPsend(reinterpret_cast<char*>(&data), sizeof(data));

    char res[50];
    size_t sz = client.TCPrecv(res, 50);
    if (sz > 0)
        std::cout << res;
}
