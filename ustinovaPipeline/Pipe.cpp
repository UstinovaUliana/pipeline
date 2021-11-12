#include "Pipe.h"
#include <iostream>;
using namespace std;

int Pipe::maxId = 0;
Pipe::Pipe(int id)
{
    ++maxId;
    this->id=id;
    this->rem = false;
    do {
        cin.clear();
        cin.ignore(2000, '\n');
        cout << "������� ������� �����, �� (50-2000):";
        cin >> this->d;
    } while (cin.fail() || this->d < 50 || this->d>2000);
    do {
        cin.clear();
        cin.ignore(2000, '\n');
        cout << "������� ����� �����, �� (0.05-10000):";
        cin >> this->l;
    } while (cin.fail() || this->l < 0.05 || this->l>10000);

}

Pipe::Pipe()
{
    ++maxId;
}

Pipe::~Pipe()
{
}

void Pipe::changePipe()
{
    this->rem = !this->rem;
    cout << this;
}

Pipe Pipe::loadPipe(ifstream& fin)
{
    Pipe pipe;
    fin >> pipe.id;
    fin >> pipe.d;
    fin >> pipe.l;
    fin >> pipe.rem;
    return pipe;
}
std::ostream& operator<< (std::ostream& out, const Pipe& truba)
{
    out << endl;
    out << "�����" << endl << "Id: " << truba.id << endl << "�������: " << truba.d << "��" << endl << "�����: " << truba.l << "��" << endl << "� �������: ";
    if (truba.rem) { out << "��"; }
    else { out << "���"; }
    out << endl;
    return out;
}
