#include "Pipe.h"
#include <iostream>;
using namespace std;

int Pipe::maxId = 0;

Pipe& Pipe::CreatePipe(Pipe& p)
{
    p.id = id;
    p.rem = false;
    do {
        cin.clear();
        cin.ignore(2000, '\n');
        cout << "Введите диаметр трубы, мм (50-2000):";
        cin >> p.d;
    } while (cin.fail() || p.d < 50 || p.d>2000);
    do {
        cin.clear();
        cin.ignore(2000, '\n');
        cout << "Введите длину трубы, км (0.05-10000):";
        cin >> p.l;
    } while (cin.fail() || p.l < 0.05 || p.l>10000);
    return p;
}

Pipe::Pipe():id(++maxId)
{
}


Pipe::~Pipe()
{
}

void Pipe::changePipe()
{
    this->rem = !this->rem;
    cout << *this;
}

Pipe& Pipe::loadPipe(ifstream& fin, Pipe& pipe)
{
    fin >> pipe.id;
    fin >> pipe.d;
    fin >> pipe.l;
    fin >> pipe.rem;
    return pipe;
}
std::ostream& operator<< (std::ostream& out, const Pipe& truba)
{
    out << endl;
    out << "Труба" << endl << "Id: " << truba.id << endl << "Диаметр: " << truba.d << "мм" << endl << "Длина: " << truba.l << "км" << endl << "В ремонте: ";
    if (truba.rem) { out << "да"; }
    else { out << "нет"; }
    out << endl;
    return out;
}
