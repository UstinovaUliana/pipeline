

#include <iostream>
#include <locale.h>
#include <string>
using namespace std;

struct Pipe {
    int id;
    double d;
    double l;
    bool rem;
};

struct Stantia {
    int id;
    string name;
    int ceh;
    int cehRab;
    int eff;
};

Pipe createPipe() {
    Pipe truba;
    truba.id = 1;
    truba.rem = false;
    cout << "������� ������� �����, ��:";
    cin >> truba.d;
    cout << "������� ����� �����, ��:";
    cin >> truba.l;
    return truba;
}

Stantia createStantia() {
    Stantia stan;
    stan.id = 2;
    cout << "������� �������� ������� (�� ����������):";
    cin >> stan.name;
    cout << "������� ���������� �����:";
    cin >> stan.ceh;
    stan.cehRab = stan.ceh;
    stan.eff = 100;
    return stan;
}

void coutPipe(Pipe& truba)
{
    cout << "�����" << endl << "Id: " << truba.id << endl << "�������: " << truba.d << "��" << endl << "�����: " << truba.l << "��" << endl << "� �������: ";
    if (truba.rem) { cout << "��"; }
    else { cout << "���"; }
    cout << endl;
}
void coutStantia(Stantia& stan)
{
    cout << "�������" << endl << "Id: " << stan.id << endl << "��������: " << stan.name << endl << "���-�� ����� " << stan.ceh << endl << "����� � ������: " << stan.cehRab << endl << "�������������: " << stan.eff << endl;
}
int main()
{
    setlocale(LC_ALL, "Russian");
    cout << " 1. �������� ����� \n 2. �������� �� \n 3. �������� ���� �������� \n 4. ������������� ����� \n 5. ������������� �� \n 6. ��������� \n 7. ��������� \n 0. ����� \n";
    int com;
    int oldCehRab;
    bool trubaExist = false;
    bool stanExist = false;
    Pipe truba;
    Stantia stan;
    cout << "�������: ";
    cin >> com;
    
    while (com != 0) {
       
        switch (com)
        {
        case 1: {
            truba = createPipe();
            coutPipe(truba);
            trubaExist = true;
            break;
        }
        case 2: {
            stan = createStantia();
            coutStantia(stan);
            stanExist = true;
            break;
        }
        case 3: {
            if (trubaExist) {
                coutPipe(truba);
            }
            else if (stanExist) {
                coutStantia(stan);
            }
            else {
                cout << "������ �� �������" << endl;
            }
            break;
        }
        case 4: {
            if (!trubaExist) {
                cout << "����� �� �������" << endl;
            }
            else {
                truba.rem = true;
                coutPipe(truba);
            }
            break;
        }
        case 5: {
            if (!stanExist) {
                cout << "������� �� �������" << endl;
            }
            else {
                oldCehRab = stan.cehRab;
                stan.cehRab = stan.cehRab-1;
                stan.eff = stan.cehRab*100/oldCehRab;
                coutStantia(stan);
            }
            break;
        }
        case 0: {
            return 0;
            break;
        }
        default: {
            cout << "��� ����� �������.\n";
            break;
        }
        }
        cout << "�������: ";
        cin >> com;
        if (!cin) {
            cin.clear();
            cin.ignore(100);
            cout << "������� ����� �������.";
        }
    }
}
    //+���� �� �����
    //� �������� ������� ��������� ����
    //���� � �������� ������� �����, ���� ���������� (� ��������)
    //+���������� � ������, ������� �����
    //+������� ����� ����� ���������
    //+���� ����� 0, ������ �����, ���� ������, "��� ����� �������"
    //������������ ���� ����� 
    //������ �� �����, ���� � ����
   




