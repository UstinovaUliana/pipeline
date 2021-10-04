

#include <iostream>
#include <locale.h>
#include <string>
#include <fstream>
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
        cout << "������� ����� �����, �� (0.05-100):";
        cin >> truba.l;
     } while (cin.fail() || truba.l < 0.05 || truba.l>100);
    
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
    stan.cehRab = stan.ceh;
    stan.eff = 100;
    return stan;
}

Pipe loadPipe() {
    Pipe truba;
    ifstream fin;
    fin.open("InTruba.txt", ios::in);
    if (fin.is_open()) {
        fin >> truba.id;
        fin >> truba.d;
        fin >> truba.l;
        fin >> truba.rem;
        fin.close();
    }
    return truba;
}

Stantia loadStantia() {
    Stantia stan;
    ifstream fin;
    fin.open("InStantia.txt", ios::in);
    if (fin.is_open()) {
        fin >> stan.id;
        fin >> stan.name;
        fin >> stan.ceh;
        fin >> stan.cehRab;
        fin >> stan.eff;
        fin.close();
    }
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

void savePipe(Pipe& truba)
{
    ofstream fout;
    fout.open("OutTruba.txt", ios::out);
    if (fout.is_open()) {
        fout << "�����" << endl << "Id: " << truba.id << endl << "�������: " << truba.d << "��" << endl << "�����: " << truba.l << "��" << endl << "� �������: ";
        if (truba.rem) { fout << "��"; }
        else { fout << "���"; }
        fout << endl;
        fout.close();
    }
    
}
void saveStantia(Stantia& stan)
{
    ofstream fout;
    fout.open("OutStantia.txt", ios::out);
    if (fout.is_open()) {
        fout << "�������" << endl << "Id: " << stan.id << endl << "��������: " << stan.name << endl << "���-�� ����� " << stan.ceh << endl << "����� � ������: " << stan.cehRab << endl << "�������������: " << stan.eff << endl;
        fout.close();
    }
    
}
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
    int oldCehRab;
    oldCehRab = stan.cehRab;
    if (stan.cehRab >= 1) {
        stan.cehRab = stan.cehRab - 1;
    }
    else { stan.cehRab = stan.cehRab; };
    stan.eff = stan.cehRab * 100 / oldCehRab;
    coutStantia(stan);
}
int main()
{
    setlocale(LC_ALL, "Russian");
    //cout << " 1. �������� ����� \n 2. �������� �� \n 3. �������� ���� �������� \n 4. ������������� ����� \n 5. ������������� �� \n 6. ��������� \n 7. ��������� \n 0. ����� \n";
    menu();
    cout << "����� ������, ������� enter.";
    int com;
    bool trubaExist = false;
    bool stanExist = false;
    Pipe truba;
    Stantia stan;
    do {
        cin.clear();
        cin.ignore(2000, '\n');
        cout << "�������: ";
        cin >> com;
    } while (cin.fail());
    
    while (1) {
       
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
             if (stanExist) {
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
            if (trubaExist) {
                savePipe(truba);
            }
            if (stanExist) {
                saveStantia(stan);
            }
            else {
                cout << "������ �� �������" << endl;
            }
            cout << "���������!";
            break;
        }
        case 7: {
            truba = loadPipe();
            coutPipe(truba);
            trubaExist = true;
            stan = loadStantia();
            coutStantia(stan);
            stanExist = true;
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
        menu();
        do {
            cin.clear();
            cin.ignore(2000, '\n');
            cout << "�������: ";
            cin >> com;
        } while (cin.fail());
        
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
   




