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
    cout << "Id: " << truba.id << endl << "Диаметр: " << truba.d << endl << "Длина: " << truba.l << endl << "В ремонте: " << truba.rem << endl;
}
void coutStantia(Stantia& stan)
{
    cout << "Id " << stan.id << endl << "Название: " << truba.name << endl << "Кол-во цехов " << truba.ceh << endl << "Цехов в работе: " << truba.cehRab << endl << "Эффективность: " << truba.eff << endl;
}

Pipe createPipe() {
    Pipe truba;
    truba.id = 0;
    truba.rem = false;
    cout << "Введите диаметр трубы:\n";
    cin >> truba.d;
    cout << "Введите длину трубы:\n";
    cin >> truba.l;
    return truba;
}

Stantia createStantia() {
    Stantia stan;
    stan.id = 0;
    cout << "Введите название станции:\n";
    cin >> stan.name;
    stan.ceh = 30;
    stan.cehRab = 30;
    stan.eff = 100;
    return stan;
}


int main()
{
    setlocale(LC_ALL, "Russian");
    cout << " 1. Добавить трубу \n 2. Добавить КС \n 3. Просмотр всех объектов \n 4. Редактировать трубу \n 5. Редактировать КС \n 6. Сохранить \n 7. Загрузить \n 0. Выход \n";
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




