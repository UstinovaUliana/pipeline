#include <iostream>
#include <locale.h>
#include <string>
#include <fstream>
#include "ustinovaPipeline.h"
#include "Pipe.h"
#include "Stantia.h"
#include "Header.h"
#include <unordered_map>
using namespace std;

void saveAll(unordered_map <int, Pipe> truby, unordered_map <int, Stantia> stantii)
{
    ofstream fout;
    cout << "������� �������� �����: ";
    string ofileName;
    cin >> ws;
    getline(cin, ofileName);
    fout.open(ofileName+".txt", ios::out);
  
    if (fout.is_open()) {
        fout << Pipe::maxId<<endl;
        fout << Stantia::maxId << endl;
        for (auto& [id,t]:truby) {
            fout << t << endl;
        }
        for (auto& [id, s] : stantii) {
            fout << s << endl;
        }
        fout.close();
    }
}

void loadAll(unordered_map <int, Pipe>& truby, unordered_map <int, Stantia>& stantii)
{
    ifstream fin;
    cout << "������� �������� �����: ";
    string ifileName;
    cin >> ws;
    getline(cin, ifileName);
    fin.open(ifileName + ".txt", ios::in);
    if (fin.is_open())
    {
        int wpId;
        int wsId;
        string type;
        truby.clear();
        stantii.clear(); 
        fin >> wpId;
        fin >> wsId;
        while (!fin.eof()) {
           
            getline(fin, type);
            if (type == "Truba") {
                Pipe p;
                fin >> p;
                truby.emplace(p.getId(), p);
            }
            if (type == "Stantia") {
                Stantia s;
                fin >> s;
                stantii.emplace(s.getId(), s);
            }
        }
        Pipe::maxId = wpId;
        Stantia::maxId = wsId;
        fin.close();
    }
    else cout << "�� �����������." << endl;
}
void menu()
{
    cout << " 1. �������� ����� \n 2. �������� �� \n 3. �������� ���� �������� \n 4. ������������� ����� \n 5. ������������� �� \n 6. ��������� \n 7. ��������� \n 8. ����� ���� � ������� \n 9. ����� ������� �� �������� ��������� ����� (������ ���������) \n 10. ����� ���� �� �������� \n 0. ����� \n";
    cout << "________________________________" << endl;
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

template<typename T, typename Obj>

using filter = bool(*)(const Obj& truba, T param);

bool checkRem(const Pipe& truba, bool param) {
    return truba.rem == param;
}
bool checkCehNrab(const Stantia& stan, int param) {
    return ((stan.ceh - stan.cehRab) * 100 / stan.ceh) >= param;
}
bool checkName(const Stantia& stan, string param) {
    return stan.name == param;
}
template<typename T, typename Obj>

vector<int> findObject(const unordered_map<int, Obj>& object, filter<T,Obj> f, T param)
{
    vector<int> found;
    for (auto [id,o] : object)
    {
        if (f(o, param))
            found.push_back(id);
    }

    return found;
}

int main()
{
   
    setlocale(LC_ALL, "Russian");
    int com;
    unordered_map <int, Pipe> truby;
    unordered_map <int, Stantia> stantii;

    while (1) {
        menu();
        command(com);

        switch (com)
        {
        case 1: {
            Pipe p;
            cin >> p;
            truby.emplace(p.getId(), p);
            cout<< truby[p.getId()]<<endl;
            break;
        }
        case 2: {
            Stantia s;
            cin >> s;
            stantii.emplace(s.getId(), s);
            cout << stantii[s.getId()] << endl;
            break;
        }
        case 3: {
            if (truby.size()==0)
                cout <<endl<< "����� �� �������" << endl;
            else  for (auto [id, p] : truby)
                cout << p;
             if (stantii.size()==0)
                 cout <<endl<< "������� �� �������" << endl;
             else  for (auto [id, s] : stantii)
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
                auto p = truby.find(id);
                if (p != truby.end())
                    truby[id].changePipe();
            }
            break;
        }
        case 5: {
            if (stantii.size() == 0)
                cout << endl << "������� �� �������" << endl;
            else {
                cout << endl << "������� id ������: ";
                int id;
                id = getInt();
                auto st = stantii.find(id);// ].changeStan();
                if (st != stantii.end())
                    stantii[id].changeStan();
            }
            break;
        }
        case 0: {
            return 0;
            break;
        }
        
        case 6: {
            saveAll(truby, stantii);
            cout << "���������!" << endl;
            break;
        }
        case 7: {
            loadAll(truby, stantii);
            cout << "���������!" << endl;
            break;
        }
        case 8: {
            bool vremonte=true;
            vector <int> TR= findObject(truby, checkRem, vremonte);
            if (TR.size() == 0) {
                cout << "��� ����� � ������" << endl;
                break;
            }
            else {
            for (int i : TR) cout << truby[i];
            int com2;
            cout << "0.�����\n1.������� ����� \n2.��������� �����\n";
            command(com2);
            switch (com2) {
            case 0: {
                break;
            }

            case 1: {
                for (int i : findObject(truby, checkRem, vremonte))
                    truby.erase(i);
                break;
            }
            case 2: {
                for (int i : findObject(truby, checkRem, vremonte))
                    truby[i].changePipe();
                break;
            }
            default: {
                cout << "��� ����� �������.\n";
                break;
            }
            }
            }
            break;
        }
        case 9: {
            int perCehNrab;
            cout << "������� ������� ��������� �����: ";
            perCehNrab=getInt();
            for (int i :findObject(stantii, checkCehNrab, perCehNrab))
                cout << stantii[i];
            break;
        }
        
        case 10: {
            string name = "";
            do {
                cout << "������� �������� ������� (�� ����������):";
                getline(cin >> ws, name);

            } while (cin.fail());
            for (int i : findObject(stantii, checkName, name))
                cout << stantii[i];
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
