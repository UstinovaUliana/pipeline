#include "Stantia.h"
#include "Header.h"
#include <iostream>
#include <string>
using namespace std;
int Stantia::maxId = 0;


std::istream& operator>> (std::istream& in, Stantia& s)
{
    do {
        cout << "Введите название станции (на английском) и дважды нажмите Enter:";
        getline(cin>>ws,s.name);
        
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
    return in;
}

Stantia::Stantia():id(++maxId)
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




std::ostream& operator<< (std::ostream& out, const  Stantia& stan)
{
    out << endl;
    out << "Станция" << endl << "Id: " << stan.id << endl << "Название: " << stan.name << endl 
        << "Кол-во цехов: " << stan.ceh << endl << "Цехов в работе: " << stan.cehRab << endl << "Эффективность: " << stan.eff << endl;
    return out;
}
std::ifstream& operator>> (std::ifstream& fin, Stantia& stan)
{
    fin >> stan.id;
    getline(fin >> ws, stan.name);
    fin >> stan.ceh;
    fin >> stan.cehRab;
    fin >> stan.eff;
    fin >> stan.kolvPipIn;
    for (int i = 0; i < stan.kolvPipIn; i++) {
        int idIni;
        fin >> idIni;
        stan.PipIn.emplace(idIni);
    }
    fin >> stan.kolvPipOut;
    for (int i = 0; i < stan.kolvPipOut; i++) {
        int idOuti;
        fin >> idOuti;
        stan.PipOut.emplace(idOuti);
    }

    return fin;
}


std::ofstream& operator<< (std::ofstream& out, Stantia& s) {


    out << "Stantia" << endl << s.id << endl << s.name << endl 
       << s.ceh << endl << s.cehRab << endl << s.eff << endl;
    s.kolvPipIn = s.PipIn.size();
    s.kolvPipOut = s.PipOut.size();
    out << s.kolvPipIn;
    for (auto i : s.PipIn) out << endl << i;
    out << endl <<  s.kolvPipOut;
    for (auto i : s.PipOut) out << endl << i;
    return out;
}