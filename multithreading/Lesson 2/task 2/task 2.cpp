#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
#include <vector>
#include <random>
#include <exception>

using conVar = std::condition_variable;


class massag {
public:
    int countThread;
    std::vector<int> vecProgres;
    std::vector<std::chrono::duration<double, std::ratio<1, 1000>>> vecTime;
    std::vector<bool> endTime;
    std::vector<std::vector<bool>> haveErr;
    int maxBar;
    bool ischange;
    
    massag(int c, int m) : countThread(c), maxBar(m), ischange(false) {
        using namespace std;
        vecProgres.resize(c, 0);
        vecTime.resize(c, 0ms);
        endTime.resize(c, false);
        haveErr.resize(c, vector<bool>(m, false));

    }
    bool changedFunc() { return ischange; }
};


void printBars(std::mutex& mtx, conVar& cond, std::vector<std::thread::id> vecId, massag& mass/*, bool& forBar*/) {    
    bool endWhile = false;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);    

    while (!endWhile) {
        std::unique_lock<std::mutex> mut(mtx);        
        cond.wait(mut, [&]() {return mass.changedFunc(); });
        std::cout << "\x1B[2J\x1B[H";        
        mass.ischange = false;
        bool tempEnd = true;
        
        std::cout << std::left;
        std::cout << std::setw(2) << "N" << std::setw(6) << " ID" << "  " << std::setw(mass.maxBar) << "progres" << " Time" <<std::endl;
        for (int i = 0; i < mass.countThread; ++i) {
            std::cout << std::setw(2) << i + 1 << " " << std::setw(6) << vecId[i] << " ";
            int progres = mass.vecProgres[i];

            for (int j = 0; j < progres; ++j) {

                if(mass.haveErr[i][j]==false)
                    std::cout << char(0xDB);
                else {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    std::cout << char(0xDB);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            }
            for (int j = mass.maxBar; j > progres; --j) {
                std::cout << " ";
            }
            if (mass.endTime[i]) {
                std::cout << " " << mass.vecTime[i].count() <<"ms";
            }
            std::cout << std::endl;
            tempEnd = tempEnd && mass.endTime[i];
        }
        endWhile = tempEnd;
    }
}

void bar(std::mutex& mtx, conVar& cv, massag& mass, int i/*, bool& forBar*/) {
    using namespace std::chrono;
    bool ranWhile = true;
    std::srand(i * time(NULL));
    auto startTime = std::chrono::steady_clock::now();
    
    while (ranWhile) {        
        std::chrono::milliseconds sleepTime(std::rand() % 400 + 300);

        std::this_thread::sleep_for(sleepTime);
        std::lock_guard<std::mutex> mut(mtx);

        try {
            if (std::rand() % 8 == 1)
                throw std::exception();
        }
        catch (std::exception e) {
            mass.haveErr[i][mass.vecProgres[i]] = true;
        }

        ++mass.vecProgres[i];
        mass.ischange = true;
        
        ranWhile = mass.vecProgres[i] < mass.maxBar;
        cv.notify_one();

    }
    std::lock_guard<std::mutex> mut2(mtx);
    
    auto endTime = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::ratio<1, 1000>> time = endTime - startTime;    
    mass.endTime[i] = true;
    mass.vecTime[i] = time;
    mass.ischange = true;
    cv.notify_one();
}


int main()
{
    int countTrd = 14;
    int maxBar = 12;
    //bool forCVBar = false;
    std::vector<std::thread> vecTrd;
    std::vector<std::thread::id> vecId;
    
    conVar cvBar;    
    std::mutex mut;
    
    massag mass(countTrd, maxBar);
    for (int i = 0; i < countTrd; ++i) {
        vecTrd.push_back(std::thread(bar, std::ref(mut), std::ref(cvBar), std::ref(mass), i/*, std::ref(forCVBar)*/));
        vecId.push_back(vecTrd[i].get_id());
    }

    std::thread print(printBars, std::ref(mut), std::ref(cvBar), vecId, std::ref(mass)/*, std::ref(forCVBar)*/);
    print.join();

    for (int i = 0; i < countTrd; ++i) {
        vecTrd[i].join();
    }
}
