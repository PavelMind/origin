#include <iostream>
#include <thread>
#include <chrono>

void print(int v) {
#ifdef _WIN32
    std::system("cls");
#else
    std::cout << "\x1B[2J\x1B[H";
#endif
    std::cout << v;
}

void queue(int count, int& var) {
    using namespace std; //без него не принимает 1s
    for (int i = 0; i < count; ++i) {        
        ++var;        
        print(var);
        std::this_thread::sleep_for(1s);
    }
}

void operatorionist(int& var){
    using namespace std;
    while (true) {
        if (var > 0) {
            --var;
            print(var);
            std::this_thread::sleep_for(2s);
        }
        else {
            std::this_thread::sleep_for(2s);//нет очереди
            if (var > 0)
                continue;
            else
                break;
        }

    }
}

int main()
{
    int count;
    std::cout << "count: ";
    std::cin >> count;
    std::cout << "\n";

    int var = 0;
    std::thread t1(queue, count, std::ref(var));
    std::thread t2(operatorionist, std::ref(var));
    t1.join();
    t2.join();

    std::cout << "\nEnd of queue";
}
