#include "Stantia.h"
#include <iostream>;
using namespace std;
int Stantia::maxId = 0;
Stantia::Stantia(int id)
{
    this->id = id;
    do {
        cout << "������� �������� ������� (�� ����������) � ������ ������� Enter:";
        getline(cin >> ws, this->name);

    } while (cin.fail());

    do {
        cin.clear();
        cin.ignore(2000, '\n');
        cout << "������� ���-�� �����: ";
        cin >> this->ceh;
    } while (cin.fail() || this->ceh < 1 || this->ceh>10);
    this->cehRab = 1;
    this->eff = 100 * this->cehRab / this->ceh;
    do {
        cin.clear();
        cin.ignore(2000, '\n');
        cout << "������� �������������: ";
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
    cout << "������� ���-�� ������� �����: ";
    cin >> this->cehRab;
    while (this->cehRab > this->ceh || this->cehRab < 0) {
        cin.clear();
        cin.ignore(2000, '\n');
        cout << "������� ���-�� ������� �����: ";
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
    out << "�������" << endl << "Id: " << stan.id << endl << "��������: " << stan.name << endl << "���-�� �����: " << stan.ceh << endl << "����� � ������: " << stan.cehRab << endl << "�������������: " << stan.eff << endl;
    return out;
}