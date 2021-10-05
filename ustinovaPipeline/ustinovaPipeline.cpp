

#include <iostream>
#include <locale.h>
#include <string>
#include <fstream>
#include "ustinovaPipeline.h"
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
    do {
        cin.clear();
        cin.ignore(2000, '\n');
        cout << "������� ������� �����, �� (50-2000):";
        cin >> truba.d;
    } while (cin.fail() || truba.d < 50 || truba.d>2000);
     do {
         cin.clear();
         cin.ignore(2000, '\n');
        cout << "������� ����� �����, �� (0.05-10000):";
        cin >> truba.l;
     } while (cin.fail() || truba.l < 0.05 || truba.l>10000);
    
    return truba;
}

Stantia createStantia() {
    Stantia stan;
    stan.id = 2;
    do {
        cout << "������� �������� ������� (�� ����������) � ������ ������� Enter:";
        getline(cin>>ws, stan.name);
  
    } while (cin.fail());
    
    do {
        cin.clear();
        cin.ignore(2000, '\n');
        cout << "������� ���������� ����� (1-10):";
        cin >> stan.ceh;
    } while (cin.fail() || stan.ceh < 1 || stan.ceh>10);
    stan.cehRab = 1;
    stan.eff = 100*stan.cehRab/stan.ceh;
    do {
        cin.clear();
        cin.ignore(2000, '\n');
        cout << "������� �������������: ";
        cin >> stan.eff;
    } while (cin.fail());
    return stan;
}

Pipe loadPipe(ifstream& fin) {
    Pipe truba = {};

        fin >> truba.id;
        fin >> truba.d;
        fin >> truba.l;
        fin >> truba.rem;

    return truba;
}

Stantia loadStantia(ifstream& fin) {
    Stantia stan;

    fin >> stan.id;
    getline(fin >> ws, stan.name);
    fin >> stan.ceh;
    fin >> stan.cehRab;
    fin >> stan.eff;

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
    cout << "�������" << endl << "Id: " << stan.id << endl << "��������: " << stan.name << endl << "���-�� �����: " << stan.ceh << endl << "����� � ������: " << stan.cehRab << endl << "�������������: " << stan.eff << endl;
}

void saveAll(Pipe& truba, Stantia& stan)
{
    ofstream fout;
    fout.open("Out.txt", ios::out);
    if (fout.is_open()) {
        fout << truba.id << endl << truba.d << endl << truba.l << endl << truba.rem;
        fout << endl;
        fout << stan.id << endl << stan.name << endl << stan.ceh << endl << stan.cehRab << endl << stan.eff << endl;
        fout.close();
    }
    
}
//void saveStantia(Stantia& stan)
//{
//    ofstream fout;
//    fout.open("Out.txt", ios::out);
//    if (fout.is_open()) {
//        fout << stan.id << endl  << stan.name << endl  << stan.ceh << endl  << stan.cehRab << endl  << stan.eff << endl;
//        fout.close();
//    }
//    
//}
void menu()
{
    cout << " 1. �������� ����� \n 2. �������� �� \n 3. �������� ���� �������� \n 4. ������������� ����� \n 5. ������������� �� \n 6. ��������� \n 7. ��������� \n 0. ����� \n";
}

void changePipe(Pipe& truba)
{
    truba.rem = true;
    coutPipe(truba);

}
void changeStan(Stantia& stan)
{  
    cout << "������� ���-�� ������� �����: ";
    cin >> stan.cehRab;
    while (stan.cehRab > stan.ceh || stan.cehRab < 0) {
        cin.clear();
        cin.ignore(2000, '\n');
        cout << "������� ���-�� ������� �����: ";
        cin >> stan.cehRab;
    }
    coutStantia(stan);
}
void command(int& com)
{
    cout << "�������: ";
    cin >> com;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(2000, '\n');
        cout << "�������: ";
        cin >> com;
    };
}
int main()
{
    setlocale(LC_ALL, "Russian");
    int com;
    bool trubaExist = false;
    bool stanExist = false;
    Pipe truba;
    Stantia stan;

    while (1) {
        menu();
        command(com);

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
            else cout << "����� �� �������" << endl;
             if (stanExist) {
                coutStantia(stan);
            }
            else  cout << "������� �� �������" << endl;
    
            break;
        }
        case 4: {
            if (!trubaExist) {
                cout << "����� �� �������" << endl;
            }
            else {
                changePipe(truba);
            }
            break;
        }
        case 5: {
            if (!stanExist) {
                cout << "������� �� �������" << endl;
            }
            else {
                changeStan(stan);
            }
            break;
        }
        case 0: {
            return 0;
            break;
        }
        
        case 6: {
            if (!stanExist) {
                stan = {};
            }
            if (!trubaExist) {
                truba = {};
            }
            saveAll(truba, stan);
            /*if (trubaExist) {
                saveAll(truba,stan);
            }
            if (stanExist) {
                saveAll(stan);
            }
            else {
                cout << "������ �� �������" << endl;
            }*/

            cout << "���������!" << endl;
            break;
        }
        case 7: {

            ifstream fin;
            fin.open("Out.txt", ios::in);
            if (!fin.is_open())
            {
                cout<<"�� �����������."<<endl;
                break;
            }
            truba = loadPipe(fin);
            stan = loadStantia(fin);
            fin.close();

            trubaExist = truba.id > 0;
            stanExist = stan.id > 0;
            break;
        }
        /*if (cin.fail()) {
            cout << "������� �����.\n";
            break;
        }*/
        default: {
            cout << "��� ����� �������.\n";
            break;
        }
        
        }

        
    }
}
    //+���� �� �����
    //+� �������� ������� ��������� ����
    //+���������� � ������, ������� �����
    //+������� ����� ����� ���������
    //+���� ����� 0, ������ �����, ���� ������, "��� ����� �������"
    //+������������ ���� ����� 
    //+������ �� �����, ���� � ����
    //+���� � �������������� - ��������
    //+�������� ����� �������
   




