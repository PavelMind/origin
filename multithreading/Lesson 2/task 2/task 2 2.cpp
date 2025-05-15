#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
#include <vector>
#include <queue>

using conVar = std::condition_variable;



class massag {
public:
    int countThread;
    std::vector<int> vecProdres;
    std::vector<std::chrono::duration<double, std::ratio<1, 1000>>> vecTime;
    std::vector<bool> endTime;
    int maxBar;
    bool ischange;
    
    massag(int c, int m) : countThread(c), maxBar(m), ischange(false) {
        using namespace std;
        vecProdres.resize(c, 0);
        vecTime.resize(c, 0ms);
        endTime.resize(c, false);
    }
    bool changedFunc() { return ischange; }
};

//bool tmpf(bool& t) { return t; }

void printBars(std::mutex& mtx, conVar& cond, std::vector<std::thread::id> vecId, massag& mass/*, bool& forBar*/) {    
    bool endWhile = false;

    while (!endWhile) {
        std::unique_lock<std::mutex> mut(mtx);
        //cond.wait(mut, tmpf(forBar) );
        cond.wait(mut, mass.changedFunc());
        std::cout << "\x1B[2J\x1B[H";
        //forBar = false;
        mass.ischange = false;

        bool tempEnd = true;
        for (int i = 0; i < mass.countThread; ++i) {
            std::cout << std::setw(2) << i << " " << std::setw(8) << vecId[i] << " " << std::setw(mass.maxBar);

            for (int j = 0; j < mass.vecProdres[i]; ++j) {
                std::cout << 0xDB;
            }
            if (mass.endTime[i]) {
                std::cout << " " << mass.vecTime[i].count();
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
    auto startTime = std::chrono::steady_clock::now();

    while (ranWhile) {
        std::this_thread::sleep_for(500ms);
        std::lock_guard<std::mutex> mut(mtx);
        ++mass.vecProdres[i];
        mass.ischange = true;
        ranWhile = mass.vecProdres[i] < mass.maxBar;
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
    int countTrd = 4;
    int maxBar = 12;
    //bool forCVBar = false;
    std::vector<std::thread> vecTrd(countTrd);
    std::vector<std::thread::id> vecId;
    
    conVar cvBar;    
    std::mutex mut;
    
    massag mass(countTrd, maxBar);
    for (int i = 0; i < countTrd; ++i) {
        vecTrd.push_back(std::thread(bar, std::ref(mut), std::ref(cvBar), std::ref(mass), i/*, std::ref(forCVBar)*/));
        vecId[i] = vecTrd[i].get_id();
    }

    std::thread print(printBars, std::ref(mut), std::ref(cvBar), vecId, std::ref(mass)/*, std::ref(forCVBar)*/);
    print.join();

    for (int i = 0; i < countTrd; ++i) {
        vecTrd[i].join();
    }
}
