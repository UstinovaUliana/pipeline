// ustinovaPipeline.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <locale.h>
using namespace std;

struct Pipe {
    int id;
    int d;
    int l;
    bool rem;
};

struct Stantia {
    int id;
    string name;
    int ceh;
    int cehRab;
    int eff;
};
void coutPipe(Pipe& truba)
{
    cout << "Id: " << truba.id << endl << "�������: " << truba.d << endl << "�����: " << truba.l << endl << "� �������: " << truba.rem << endl;
}
void coutStantia(Stantia& stan)
{
    cout << "Id " << stan.id << endl << "��������: " << truba.name << endl << "���-�� ����� " << truba.ceh << endl << "����� � ������: " << truba.cehRab << endl << "�������������: " << truba.eff << endl;
}

Pipe createPipe() {
    Pipe truba;
    truba.id = 0;
    truba.rem = false;
    cout << "������� ������� �����:\n";
    cin >> truba.d;
    cout << "������� ����� �����:\n";
    cin >> truba.l;
    return truba;
}

Stantia createStantia() {
    Stantia stan;
    stan.id = 0;
    cout << "������� �������� �������:\n";
    cin >> stan.name;
    stan.ceh = 30;
    stan.cehRab = 30;
    stan.eff = 100;
    return stan;
}


int main()
{
    setlocale(LC_ALL, "Russian");
    cout << " 1. �������� ����� \n 2. �������� �� \n 3. �������� ���� �������� \n 4. ������������� ����� \n 5. ������������� �� \n 6. ��������� \n 7. ��������� \n 0. ����� \n";
    int a;
    cin >> a;
    if (a == 1) {
        Pipe truba = createPipe();
        coutPipe(truba);
    }
    if (a == 2) {
        Stantia stan = createStantia();
        coutStantia(stan);
    }
   // if (a == 4) {
    //truba.rem = true;
    //coutPipe(truba);
}
   

}




