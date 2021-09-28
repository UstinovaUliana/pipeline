// ustinovaPipeline.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <locale.h>
#include <string>
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

Pipe createPipe() {
    Pipe truba;
    truba.id = 1;
    truba.rem = false;
    cout << "Введите диаметр трубы:\n";
    cin >> truba.d;
    cout << "Введите длину трубы:\n";
    cin >> truba.l;
    return truba;
}

Stantia createStantia() {
    Stantia stan;
    stan.id = 2;
    cout << "Введите название станции:\n";
    cin >> stan.name;
    stan.ceh = 30;
    stan.cehRab = 30;
    stan.eff = 100;
    return stan;
}

void coutPipe(Pipe& truba)
{
    cout << "Труба" << endl << "Id: " << truba.id << endl << "Диаметр: " << truba.d << endl << "Длина: " << truba.l << endl << "В ремонте: " << truba.rem << endl;
}
void coutStantia(Stantia& stan)
{
    cout << "Станция" << endl << "Id " << stan.id << endl << "Название: " << stan.name << endl << "Кол-во цехов " << stan.ceh << endl << "Цехов в работе: " << stan.cehRab << endl << "Эффективность: " << stan.eff << endl;
}
int main()
{
    setlocale(LC_ALL, "Russian");
    cout << " 1. Добавить трубу \n 2. Добавить КС \n 3. Просмотр всех объектов \n 4. Редактировать трубу \n 5. Редактировать КС \n 6. Сохранить \n 7. Загрузить \n 0. Выход \n";
    int a;
    bool trubaExist=false;
    bool stanExist=false;    
    Pipe truba;
    Stantia stan;
    cin >> a;
    while (a != 0) {
    
        if (a == 1) {
            truba = createPipe();
            coutPipe(truba);
           trubaExist=true;
        }
        if (a == 2) {
            stan = createStantia();
            coutStantia(stan);
            stanExist=true;
        }
        if ((a == 3)&&(trubaExist)) {
            coutPipe(truba);
        }
        if ((a == 3) && (stanExist)) {
            coutStantia(stan);
        }
        if ((a == 3) && (!trubaExist) && (!stanExist)) {
            cout << "Ничего не создано"<<endl;
        }
        if ((a == 4) && (!trubaExist)) {
            cout << "Труба не создана"<<endl;
        }
        if ((a == 4) && (trubaExist)) {
            truba.rem = true;
            coutPipe(truba);
        }
        if ((a == 5) && (!stanExist)) {
            cout << "Станция не создана"<<endl;
        }
        if ((a == 5) && (stanExist)) {
            stan.cehRab = 20;
            stan.eff = 66;
            coutStantia(stan);
        }
        cin >> a;
    }
    
    //цехи по вводу
    //в название водятся несколько слов
    //если в название вводить цифры, тебя поправляют (и наоборот)
    //переменную а убрать, сделать кейсы
    //нецелые числа чтобы вводились
    //если число 0, ритурн брейк, если другие, "нет такой команды"
    //некорректный ввод чисел 
}
   




