// ustinovaPipeline.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <locale.h>
#include <string>
using namespace std;

struct Pipe {
    int id;
    int d;
    int l;
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
    cout << "������� ������� �����:\n";
    cin >> truba.d;
    cout << "������� ����� �����:\n";
    cin >> truba.l;
    return truba;
}

Stantia createStantia() {
    Stantia stan;
    stan.id = 2;
    cout << "������� �������� �������:\n";
    cin >> stan.name;
    stan.ceh = 30;
    stan.cehRab = 30;
    stan.eff = 100;
    return stan;
}

void coutPipe(Pipe& truba)
{
    cout << "�����" << endl << "Id: " << truba.id << endl << "�������: " << truba.d << endl << "�����: " << truba.l << endl << "� �������: " << truba.rem << endl;
}
void coutStantia(Stantia& stan)
{
    cout << "�������" << endl << "Id " << stan.id << endl << "��������: " << stan.name << endl << "���-�� ����� " << stan.ceh << endl << "����� � ������: " << stan.cehRab << endl << "�������������: " << stan.eff << endl;
}
int main()
{
    setlocale(LC_ALL, "Russian");
    cout << " 1. �������� ����� \n 2. �������� �� \n 3. �������� ���� �������� \n 4. ������������� ����� \n 5. ������������� �� \n 6. ��������� \n 7. ��������� \n 0. ����� \n";
    int a;
    bool trubaExist=false;
    bool stanExist=false;    
    Pipe truba;
    Stantia stan;
    cin >> a;
    while (a != 0) {
    
        if (a == 1) {
            truba = createPipe();
            coutPipe(truba);
           trubaExist=true;
        }
        if (a == 2) {
            stan = createStantia();
            coutStantia(stan);
            stanExist=true;
        }
        if ((a == 3)&&(trubaExist)) {
            coutPipe(truba);
        }
        if ((a == 3) && (stanExist)) {
            coutStantia(stan);
        }
        if ((a == 3) && (!trubaExist) && (!stanExist)) {
            cout << "������ �� �������"<<endl;
        }
        if ((a == 4) && (!trubaExist)) {
            cout << "����� �� �������"<<endl;
        }
        if ((a == 4) && (trubaExist)) {
            truba.rem = true;
            coutPipe(truba);
        }
        if ((a == 5) && (!stanExist)) {
            cout << "������� �� �������"<<endl;
        }
        if ((a == 5) && (stanExist)) {
            stan.cehRab = 20;
            stan.eff = 66;
            coutStantia(stan);
        }
        cin >> a;
    }
    
    //���� �� �����
    //� �������� ������� ��������� ����
    //���� � �������� ������� �����, ���� ���������� (� ��������)
    //���������� � ������, ������� �����
    //������� ����� ����� ���������
    //���� ����� 0, ������ �����, ���� ������, "��� ����� �������"
    //������������ ���� ����� 
}
   




