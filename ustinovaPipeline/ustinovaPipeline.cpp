

#include <iostream>
#include <locale.h>
#include <string>
#include <fstream>
#include "ustinovaPipeline.h"
#include <unordered_map>
using namespace std;

struct Pipe {
    int id;
    double d;
    double l;
    bool rem;
    friend std::ostream& operator<< (std::ostream& out, const Pipe& pipe);
};

std::ostream& operator<< (std::ostream& out, const Pipe& truba)
{
    out << endl;
    out << "�����" << endl << "Id: " << truba.id << endl << "�������: " << truba.d << "��" << endl << "�����: " << truba.l << "��" << endl << "� �������: ";
    if (truba.rem) { out << "��"; }
    else { out << "���"; }
    out << endl;
    return out;
}

struct Stantia {
    int id;
    string name;
    int ceh;
    int cehRab;
    int eff;
    friend std::ostream& operator<< (std::ostream& out, const Stantia& stan);
};
std::ostream& operator<< (std::ostream& out, const  Stantia& stan)
{
    out << endl;
    out << "�������" << endl << "Id: " << stan.id << endl << "��������: " << stan.name << endl << "���-�� �����: " << stan.ceh << endl << "����� � ������: " << stan.cehRab << endl << "�������������: " << stan.eff << endl;


    return out;
}

int tc = 0;
int sc = 0;
Pipe createPipe() {
    Pipe truba;
    truba.id = ++tc;
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


int getInt()
{
    int input;
    while (1) {
        cin >> input;
        if (!cin.fail())
            return input;
        cin.clear();
        cin.ignore(2000, '\n');
    }
}

Stantia createStantia() {
    Stantia stan;
    stan.id = sc++;
    do {
        cout << "������� �������� ������� (�� ����������) � ������ ������� Enter:";
        getline(cin>>ws, stan.name);
  
    } while (cin.fail());
    
    do {
        cin.clear();
        cin.ignore(2000, '\n');
        cout << "������� ���-�� �����: ";
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

void saveAll(unordered_map <int, Pipe> truby, unordered_map <int, Stantia> stantii)
{
    ofstream fout;
    cout << "������� �������� �����: ";
    string ofileName;
    cin >> ofileName;
    fout.open(ofileName+".txt", ios::out);
    if (fout.is_open()) {
        for (int i = 0; i<=--tc; i++) {
            fout << "Truba"<<endl << truby[i].id << endl << truby[i].d << endl << truby[i].l << endl << truby[i].rem << endl;
        }
        for (int i = 0; i <= --sc; i++) {
            fout <<"Stantia" << endl << stantii[i].id << endl << stantii[i].name << endl << stantii[i].ceh << endl << stantii[i].cehRab << endl << stantii[i].eff << endl;
            
        }

        fout.close();
    }
    
}

void menu()
{
    cout << " 1. �������� ����� \n 2. �������� �� \n 3. �������� ���� �������� \n 4. ������������� ����� \n 5. ������������� �� \n 6. ��������� \n 7. ��������� \n 8. ����� ���� � ������� \n 9. ����� ������� �� �������� ��������� ����� \n 0. ����� \n";
    cout << "________________________________" << endl;
}

void changePipe(Pipe& truba)
{
    truba.rem = !truba.rem;
    cout << truba;

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
template<typename T>
using filter = bool(*)(const Pipe& truba, T param);
bool checkRem(const Pipe& truba, bool param) {
    return truba.rem == param;
}
bool chechCehRab(const Stantia& stan, int param) {
    return ((stan.ceh - stan.cehRab)*100 / stan.ceh) >= param;
}
template<typename T>
vector<int> findTrubyRem(const unordered_map<int, Pipe>& truby, filter<T> rem, T vremonte)
{
    vector <int> trubyRem;
    int i = 0;
    for (auto [id,p] : truby)
    {
        if (rem(p, vremonte))
            trubyRem.push_back(i);
        i++;
    }

    return trubyRem;
}

int main()
{
   
    setlocale(LC_ALL, "Russian");
    int com;
    Pipe truba;
    Stantia stan;
    unordered_map <int, Pipe> truby;
    unordered_map <int, Stantia> stantii;

    while (1) {
        menu();
        command(com);

        switch (com)
        {
        case 1: {
            truba = createPipe();
            truby.insert({ tc, truba });
            cout<<truba<<endl;
            break;
        }
        case 2: {
            stan = createStantia();
            stantii.insert({ --sc, stan });
            cout << stan << endl;
            break;
        }
        case 3: {
            if (truby.size()==0)
                cout <<endl<< "����� �� �������" << endl;
            for (auto [id, p] : truby)
                cout << p;
             if (stantii.size()==0)
                 cout <<endl<< "������� �� �������" << endl;
             for (auto [id, s] : stantii)
                 cout << s;
            break;
        }
        case 4: {
            if (truby.size() == 0)
                cout << endl << "����� �� �������" << endl;
            else {
                cout << endl << "������� id �����: ";
                int id;
                id=getInt();

                changePipe(truby[id]);
            }
            break;
        }
        case 5: {
            if (stantii.size() == 0)
                cout << endl << "������� �� �������." << endl;
            else {
                cout << endl << "������� id ������: ";
                int id;
                id = getInt();
                changeStan(stantii[id]);
            }
            break;
        }
        case 0: {
            return 0;
            break;
        }
        
        case 6: {
            /*if (stantii.size() == 0)
                stan = {};
            if (truby.size()==0) 
                truba = {};*/
            
            saveAll(truby, stantii);
            cout << "���������!" << endl;
            break;
        }
        case 7: {

            ifstream fin;
            cout << "������� �������� �����: ";
            string ifileName;
            cin >> ifileName;
            fin.open(ifileName+".txt", ios::in);
            if (!fin.is_open())
            {
                cout<<"�� �����������."<<endl;
                break;
            }
            string type;
            while (!fin.eof()) {
                tc = 0;
                sc = 0;
                getline(fin,type);
                if (type == "Truba") {
                 truby[tc] = loadPipe(fin);
                    tc++;
                }
                if (type == "Stantia") {
                    stantii[sc] = loadStantia(fin);
                    sc++;
                }
                
            }
            
            fin.close();

            break;
        }
        /*if (cin.fail()) {
            cout << "������� �����.\n";
            break;
        }*/
        case 8: {
            bool vremonte=true;
            for (int i :findTrubyRem(truby, checkRem, vremonte))
                cout << truby[i];

            /*for (int i : FindStudentsByFilter(stantii, chechCehRab, 50))
                cout << stantii[i];*/

            break;
        }
        default: {
            cout << "��� ����� �������.\n";
            break;
        }
        
        }
        cout << "________________________________" <<endl;
        
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
    // 
//+-�������� �����
//+-���������� � ��������

   




