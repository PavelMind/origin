#include <iostream>
#include <fstream>
#include <string>
using namespace std;


class adress {
    string sity;
    string street;
    int home;
    int namber;
public:
    adress() : sity{}, street{}, home(0), namber(0) {}
    void read(ifstream& fl) {
        fl >> sity >> street >> home >> namber;
    }
    void write(ofstream& fl) {
        fl << sity << ", " << street <<
            ", " << home << ", " << namber << "\n";
    }
    string Sity() { return sity; }
};

void sort(adress* arr, int size) {
    for (int i = 0; i < size ; i++) {
        for (int j = i; j < size; j++) {
            if (arr[i].Sity() > arr[j].Sity()) {
                adress temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

    }
}

int main()
{
    int count = 0;
    ifstream fl;
    fl.open("in.txt");
    if (!fl.is_open()) {
        std::cout << "файл не открыт 1";
        return 0;
    }
    fl >> count;
    adress* arr = new adress[count];
    for (int i = 0; i < count; i++) {
        arr[i].read(fl);
    }
    fl.close();

    sort(arr, count);

    ofstream ofl;
    ofl.open("out.txt");
    if (!ofl.is_open()) {
        std::cout << "файл не открыт 2";
        return 0;
    }
    ofl << count << "\n";
    for (int i = 0; i < count; i++) {
        arr[i].write(ofl);
    }
    ofl.close();
    delete[] arr;
    return 0;
}
