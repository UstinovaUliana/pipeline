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
        cout << "Введите диаметр трубы, мм (50-2000):";
        in >> p.d;
    } while (in.fail() || p.d < 50 || p.d>2000);
    do {
        in.clear();
        in.ignore(2000, '\n');
        cout << "Введите длину трубы, км (0.05-10000):";
        in >> p.l;
    } while (in.fail() || p.l < 0.05 || p.l>10000);
    return in;
}
std::ostream& operator<< (std::ostream& out, const Pipe& truba)
{
    out << endl;
    out << "Труба" << endl << "Id: " << truba.id << endl << "Диаметр: " << truba.d << "мм" << endl << "Длина: " << truba.l << "км" << endl << "В ремонте: ";
    if (truba.rem) { out << "да"; }
    else { out << "нет"; }
    out << endl
        <<truba.idIn << endl <<truba.idOut<<endl;
    return out;
}
std::ofstream& operator<< (std::ofstream& out, const Pipe& t)
{
    out << "Truba" << endl << t.id << endl << t.d << endl << t.l << endl << t.rem << endl;
    return out;
}
