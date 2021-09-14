// ustinovaPipeline.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

struct Pipe {
    int id;
    int d;
    bool sost;
};

struct Stantia {
    int l;
    bool rab;
};
void coutPipe(Pipe& truba)
{
    cout << "Id: " << truba.id << endl << "Диаметр: " << truba.d << endl << "Rabotaet: " << truba.sost << endl;
}

Pipe createPipe() {
    Pipe truba;
    truba.id = 0;
    truba.sost = true;
    cout << "Введите диаметр:\n";
    cin >> truba.d;
    return truba;
}

Stantia createStantia() {
    Stantia stan;
    cout << "Vvedite dlinu:\n";
    cin >> stan.l;
    stan.rab = true;
    return stan;
}

void coutStantia(Stantia& stan);

int main()
{

    Pipe truba = createPipe();
    coutPipe(truba);
    Stantia stan = createStantia();
    
    coutStantia(stan);

}

void coutStantia(Stantia& stan)
{
    cout << "Dlina: " << stan.l << endl << "Rabotaet: " << stan.rab << endl;
}


