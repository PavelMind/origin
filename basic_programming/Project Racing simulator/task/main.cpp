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
        info= L"������������ ����!\n";
        return false;
    }
    return true;
}


void chooseDistance(track*& trackRace) {
    wstring info{};
    while(true){
        wcout << info;
        cout << "������� ��������� ��� �����: ";
        int d;
        if (!correctCin(info, d)) { clear();  continue; }
        if (d <= 0) { clear(); info = L"������ ������������� ��������.\n"; continue; }
        trackRace->setDist(d);
        clear();
        break;
    }
}

void chooseTrack(track*& trackRace) {    
    wstring info{};
    while (true){        
        wcout << info;
        cout << "�������� ��� �����:\n1 - ��� ���� ����������\n2 - � �������� �����������\n3 - � ��������� �����������\n";
        int typeRace;
        if (!correctCin(info, typeRace)) { clear();  continue; }
        switch (typeRace)
        {
        case 1: trackRace = new allTrack(); break;
        case 2: trackRace = new groundTrack(); break;
        case 3: trackRace = new airTrack(); break;
        default:
            info = L"�������� ��������.\n";                       
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
    case typeTrack::all: infoRace = L"����� ��� ���� ����� ����������. ���������: " + to_wstring(trackRace->distance()); break;
    case typeTrack::air: infoRace = L"����� ��� ���������� ����������. ���������: " + to_wstring(trackRace->distance()); break;
    case typeTrack::ground: infoRace = L"����� ��� ��������� ����������. ���������: " + to_wstring(trackRace->distance()); break;
    }
    bool outWhile = false;

    while (true) {
        clear();
        wcout << info;        
        wcout << infoRace;        
        wcout << trackRace->list();
        cout << "\n�������� ���������: \n1 - ������� \n2 - �������-�������� \n3 - ������� \n4 - �������-��������� \
            \n5 - ����-������ \n6 - ��� \n7 - ����� \n0 - ��������� �����������\n";
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
        case 0: if ((trackRace->count()) < 2) { info = L"������ ���� ������ 1 ������� ����������.\n"; continue; }
              else { outWhile = true; break; }
        default:  info = L"������������ ����.\n"; continue;
        }

        if (!outWhile) {
            try {
                trackRace->registration(TS);
                info = TS->name() + L" ������� ���������������.\n";
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
    cout << "���������� �����:\n";
    for (int i = 0; i < count; ++i) {
        cout << i+1 << " �����: ";
        wcout << result[i].name;
        cout << " - �����: " << result[i].time << endl;
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

        cout << "\n�������� ��� �����? \n1 - ��\n0 - ���\n";
        int newGame;
        cin >> newGame;
        if (newGame == 0)  break;
    }
}