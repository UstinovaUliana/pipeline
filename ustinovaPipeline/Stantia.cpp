#include "Stantia.h"
#include "Header.h"
#include <iostream>;
using namespace std;
int Stantia::maxId = 0;


Stantia& Stantia::CreateStantia(Stantia& s)
{
    do {
        cout << "������� �������� ������� (�� ����������) � ������ ������� Enter:";
        getline(cin >> ws, s.name);

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
    out << "�������" << endl << "Id: " << stan.id << endl << "��������: " << stan.name << endl << "���-�� �����: " << stan.ceh << endl << "����� � ������: " << stan.cehRab << endl << "�������������: " << stan.eff << endl;
    return out;
}