#include "Pipe.h"
#include <iostream>;
using namespace std;

int Pipe::maxId = 0;

Pipe::Pipe():id(++maxId)
{
    this->idIn = 0;
    this->idOut = 0;
}

void Pipe::changePipe()
{
    this->rem = !this->rem;
    cout << *this;
}

std::ifstream& operator>> (std::ifstream& fin, Pipe& pipe)
{
    fin >> pipe.id;
    fin >> pipe.d;
    fin >> pipe.l;
    fin >> pipe.rem;
    fin >> pipe.idIn;
    fin >> pipe.idOut;
    return fin;
}
std::istream& operator>> (std::istream& in, Pipe& p)
{
    p.rem = false;
    p.idIn = 0;
    p.idOut = 0;
    do {
        in.clear();
        in.ignore(2000, '\n');
        cout << "������� ������� �����, �� (50-2000):";
        in >> p.d;
    } while (in.fail() || p.d < 50 || p.d>2000);
    do {
        in.clear();
        in.ignore(2000, '\n');
        cout << "������� ����� �����, �� (0.05-10000):";
        in >> p.l;
    } while (in.fail() || p.l < 0.05 || p.l>10000);
    return in;
}
std::ostream& operator<< (std::ostream& out, const Pipe& truba)
{
    out << endl;
    out << "�����" << endl << "Id: " << truba.id << endl << "�������: " << truba.d << "��" << endl << "�����: " << truba.l << "��" << endl << "� �������: ";
    if (truba.rem) { out << "��"; }
    else { out << "���"; }
    out << endl;
       if (truba.idIn!=0) out<< "���� � ������� "<<truba.idIn << " �� ������� " << truba.idOut << endl;
    return out;
}
std::ofstream& operator<< (std::ofstream& out, const Pipe& t)
{
    out << "Truba" << endl << t.id << endl << t.d << endl << t.l << endl << t.rem << endl<<t.idIn<<endl<<t.idOut;
    return out;
}
