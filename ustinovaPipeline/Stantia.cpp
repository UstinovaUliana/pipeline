#include "Stantia.h"
#include "Header.h"
#include <iostream>;
using namespace std;
int Stantia::maxId = 0;


Stantia& Stantia::CreateStantia(Stantia& s)
{
    do {
        cout << "Введите название станции (на английском) и дважды нажмите Enter:";
        getline(cin >> ws, s.name);

    } while (cin.fail());

    do {
        cin.clear();
        cin.ignore(2000, '\n');
        cout << "Введите кол-во цехов: ";
        cin >> s.ceh;
    } while (cin.fail() || s.ceh < 1 || s.ceh>10);
    s.cehRab = 1;
    s.eff = 100 * s.cehRab / s.ceh;
    do {
        cin.clear();
        cin.ignore(2000, '\n');
        cout << "Введите эффективность: ";
        cin >> s.eff;
    } while (cin.fail());
    return s;
}

Stantia::Stantia():id(++maxId)
{
}

Stantia::~Stantia()
{
}

void Stantia::changeStan()
{
    cout << "Введите кол-во рабочих цехов: ";
    this->cehRab=getInt();
    while (this->cehRab > this->ceh || this->cehRab < 0) {
        cin.clear();
        cin.ignore(2000, '\n');
        cout << "Введите кол-во рабочих цехов: ";
        cin >> this->cehRab;
    }
    cout << *this;
}

Stantia& Stantia::loadStantia(ifstream& fin, Stantia& stan)
{
    fin >> stan.id;
    getline(fin >> ws, stan.name);
    fin >> stan.ceh;
    fin >> stan.cehRab;
    fin >> stan.eff;
    return stan;
}


std::ostream& operator<< (std::ostream& out, const  Stantia& stan)
{
    out << endl;
    out << "Станция" << endl << "Id: " << stan.id << endl << "Название: " << stan.name << endl << "Кол-во цехов: " << stan.ceh << endl << "Цехов в работе: " << stan.cehRab << endl << "Эффективность: " << stan.eff << endl;
    return out;
}