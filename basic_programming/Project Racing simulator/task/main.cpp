#include <iostream>
#include <string>
#include <Windows.h>
#include "eagle.h"
#include "carpet.h"
#include "broom.h"
#include "camel.h"
#include "camelFast.h"
#include "centaur.h"
#include "boots.h"
#include "airTrack.h"
#include "groundTrack.h"
#include "allTrack.h"

using namespace std;

void clear() {
     std::cout << "\x1B[2J\x1B[H";
}


bool correctCin(wstring& info, int& var) {    
    cin >> var;
    if (cin.fail()) {
        cin.clear();
        std::cin.ignore(1024, '\n');
        info= L"Некорректный ввод!\n";
        return false;
    }
    return true;
}


void chooseDistance(track*& trackRace) {
    wstring info{};
    while(true){
        wcout << info;
        cout << "Введите дистанцию для гонки: ";
        int d;
        if (!correctCin(info, d)) { clear();  continue; }
        if (d <= 0) { clear(); info = L"Ведите положительное значение.\n"; continue; }
        trackRace->setDist(d);
        clear();
        break;
    }
}

void chooseTrack(track*& trackRace) {    
    wstring info{};
    while (true){        
        wcout << info;
        cout << "Выберите тип гонки:\n1 - все виды транспорта\n2 - с наземным транспортом\n3 - с воздушным транспортом\n";
        int typeRace;
        if (!correctCin(info, typeRace)) { clear();  continue; }
        switch (typeRace)
        {
        case 1: trackRace = new allTrack(); break;
        case 2: trackRace = new groundTrack(); break;
        case 3: trackRace = new airTrack(); break;
        default:
            info = L"Неверное значение.\n";                       
            clear();
            continue;
        }
        break;
    } 
    clear();
}

void registrationTS(track*& trackRace) {
    wstring info{};
    wstring infoRace{};
    switch (trackRace->type()) {
    case typeTrack::all: infoRace = L"Гонка для всех видов транспорта. Дистанция: " + to_wstring(trackRace->distance()); break;
    case typeTrack::air: infoRace = L"Гонка для воздушного транспорта. Дистанция: " + to_wstring(trackRace->distance()); break;
    case typeTrack::ground: infoRace = L"Гонка для наземного транспорта. Дистанция: " + to_wstring(trackRace->distance()); break;
    }
    bool outWhile = false;

    while (true) {
        clear();
        wcout << info;        
        wcout << infoRace;        
        wcout << trackRace->list();
        cout << "\nВыберите транспорт: \n1 - Верблюд \n2 - Верблюд-скороход \n3 - Кентавр \n4 - Ботинки-вездеходы \
            \n5 - Ковёр-самолёт \n6 - Орёл \n7 - Метла \n0 - закончить регистрацию\n";
        int typeTS;
        if (!correctCin(info, typeTS)) { clear();  continue; }
        baseTransport* TS;
        switch (typeTS) {
        case 1: TS = new camel; break;
        case 2: TS = new camelFast; break;
        case 3: TS = new centaur; break;
        case 4: TS = new boots; break;
        case 5: TS = new carpet; break;
        case 6: TS = new eagle; break;
        case 7: TS = new broom; break;        
        case 0: if ((trackRace->count()) < 2) { info = L"Должно быть больше 1 единицы транспорта.\n"; continue; }
              else { outWhile = true; break; }
        default:  info = L"Неправильный ввод.\n"; continue;
        }

        if (!outWhile) {
            try {
                trackRace->registration(TS);
                info = TS->name() + L" успешно зарегестрирован.\n";
            }
            catch (errorReg e) {
                delete TS;
                info = e.what()+L"\n";
            }
        }
        else break;
    }
    clear();
}

void outResult(resultRace& result){
    unsigned int count = result.count();    
    result.sort();    
    cout << "Результаты гонки:\n";
    for (int i = 0; i < count; ++i) {
        cout << i+1 << " место: ";
        wcout << result[i].name;
        cout << " - время: " << result[i].time << endl;
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    while (true) {
        clear();
        track* trackRace=nullptr;
        
        chooseTrack(trackRace);
        if (trackRace == nullptr)cout << "null ptr";        
        chooseDistance(trackRace);
        registrationTS(trackRace);
        resultRace result = trackRace->race();
        outResult(result);
                
        delete trackRace;

        cout << "\nПровести ещё гонку? \n1 - да\n0 - нет\n";
        int newGame;
        cin >> newGame;
        if (newGame == 0)  break;
    }
}