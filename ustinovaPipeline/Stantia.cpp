#include "Stantia.h"
#include "Header.h"
#include <iostream>
#include <string>
using namespace std;
int Stantia::maxId = 0;


std::istream& operator>> (std::istream& in, Stantia& s)
{
    do {
        cout << "������� �������� ������� (�� ����������) � ������ ������� Enter:";
        getline(cin>>ws,s.name);
        
    } while (cin.fail());

    do {
        cin.clear();
        cin.ignore(2000, '\n');
        cout << "������� ���-�� �����: ";
        cin >> s.ceh;
    } while (cin.fail() || s.ceh < 1 || s.ceh>10);
    s.cehRab = 1;
    s.eff = 100 * s.cehRab / s.ceh;
    do {
        cin.clear();
        cin.ignore(2000, '\n');
        cout << "������� �������������: ";
        cin >> s.eff;
    } while (cin.fail());
    return in;
}

Stantia::Stantia():id(++maxId)
{
}

void Stantia::changeStan()
{
    cout << "������� ���-�� ������� �����: ";
    this->cehRab=getInt();
    while (this->cehRab > this->ceh || this->cehRab < 0) {
        cin.clear();
        cin.ignore(2000, '\n');
        cout << "������� ���-�� ������� �����: ";
        cin >> this->cehRab;
    }
    
    cout << *this;
}




std::ostream& operator<< (std::ostream& out, const  Stantia& stan)
{
    out << endl;
    out << "�������" << endl << "Id: " << stan.id << endl << "��������: " << stan.name << endl 
        << "���-�� �����: " << stan.ceh << endl << "����� � ������: " << stan.cehRab << endl << "�������������: " << stan.eff << endl;
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
        cin >> idIni;
        stan.PipIn.emplace(idIni);
    }
    fin >> stan.kolvPipOut;
    for (int i = 0; i < stan.kolvPipOut; i++) {
        int idOuti;
        cin >> idOuti;
        stan.PipOut.emplace(idOuti);
    }

    return fin;
}


std::ofstream& operator<< (std::ofstream& out, Stantia& s) {


    out << "Stantia" << endl << s.id << endl << s.name << endl 
       << s.ceh << endl << s.cehRab << endl << s.eff << endl;
    out << s.kolvPipIn;
    for (auto i : s.PipIn) out << i;
    out << s.kolvPipOut;
    for (auto i : s.PipOut) out << i;
    return out;
}