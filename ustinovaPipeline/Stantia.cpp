#include "Stantia.h"
#include <iostream>;
using namespace std;
int Stantia::maxId = 0;
Stantia::Stantia(int id)
{
    this->id = id;
    do {
        cout << "Введите название станции (на английском) и дважды нажмите Enter:";
        getline(cin >> ws, this->name);

    } while (cin.fail());

    do {
        cin.clear();
        cin.ignore(2000, '\n');
        cout << "Введите кол-во цехов: ";
        cin >> this->ceh;
    } while (cin.fail() || this->ceh < 1 || this->ceh>10);
    this->cehRab = 1;
    this->eff = 100 * this->cehRab / this->ceh;
    do {
        cin.clear();
        cin.ignore(2000, '\n');
        cout << "Введите эффективность: ";
        cin >> this->eff;
    } while (cin.fail());
    ++maxId;
}

Stantia::Stantia()
{
    ++maxId;
}

Stantia::~Stantia()
{
}

void Stantia::changeStan()
{
    cout << "Введите кол-во рабочих цехов: ";
    cin >> this->cehRab;
    while (this->cehRab > this->ceh || this->cehRab < 0) {
        cin.clear();
        cin.ignore(2000, '\n');
        cout << "Введите кол-во рабочих цехов: ";
        cin >> this->cehRab;
    }
    cout << this;
}

Stantia Stantia::loadStantia(ifstream& fin)
{
    Stantia stan;
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