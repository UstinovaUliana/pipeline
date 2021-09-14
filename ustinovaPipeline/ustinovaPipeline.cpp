// ustinovaPipeline.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

struct Pipe {
    int id;
    int d;

};

void coutPipe(Pipe& truba)
{
    cout << "Id: " << truba.id << endl << "Диаметр: " << truba.d << endl;
}

Pipe createPipe() {
    Pipe truba;
    truba.id = 0;
    cout << "Введите диаметр:\n";
    cin >> truba.d;
    return truba;
}

int main()
{
    Pipe truba = createPipe();
    coutPipe(truba);
}


