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
    cout << "Введите название файла: ";
    string ofileName;
    cin >> ofileName;
    fout.open(ofileName+".txt", ios::out);
    if (fout.is_open()) {
        for (int i = 1; i<=truby.size(); i++) {
            fout << "Truba"<<endl << truby[i].id << endl << truby[i].d << endl << truby[i].l << endl << truby[i].rem << endl;
        }
        for (int i = 1; i<=stantii.size(); i++) {
            fout << "Stantia" << endl << stantii[i].id << endl << stantii[i].name << endl << stantii[i].ceh << endl << stantii[i].cehRab << endl << stantii[i].eff << endl;
        }
        fout.close();
    }
}

void loadAll(unordered_map <int, Pipe>& truby, unordered_map <int, Stantia>& stantii)
{
    ifstream fin;
    cout << "Введите название файла: ";
    string ifileName;
    cin >> ifileName;
    fin.open(ifileName + ".txt", ios::in);
    if (fin.is_open())
    {
        string type;
        truby.clear();
        stantii.clear();
        while (!fin.eof()) {
            getline(fin, type);
            if (type == "Truba") {
                Pipe p;
                truby.emplace(p.id, Pipe::loadPipe(fin, p));
            }
            if (type == "Stantia") {
                Stantia s;
                stantii.emplace(s.id, Stantia::loadStantia(fin,s));
            }
        }
        fin.close();
    }
    else cout << "Не открывается." << endl;
}
void menu()
{
    cout << " 1. Добавить трубу \n 2. Добавить КС \n 3. Просмотр всех объектов \n 4. Редактировать трубу \n 5. Редактировать КС \n 6. Сохранить \n 7. Загрузить \n 8. Поиск труб в ремонте \n 9. Поиск станций по проценту нерабочих цехов (больше введённого) \n 10. Поиск труб по названию \n 0. Выход \n";
    cout << "________________________________" << endl;
}

void command(int& com)
{
    cout << "Команда: ";
    cin >> com;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(2000, '\n');
        cout << "Команда: ";
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
            truby.emplace(p.id, p.CreatePipe(p));
            cout<< truby[p.id]<<endl;
            break;
        }
        case 2: {
            Stantia s;
            stantii.emplace(s.id, s.CreateStantia(s));
            cout << stantii[s.id] << endl;
            break;
        }
        case 3: {
            if (truby.size()==0)
                cout <<endl<< "Трубы не созданы" << endl;
            for (auto [id, p] : truby)
                cout << p;
             if (stantii.size()==0)
                 cout <<endl<< "Станции не созданы" << endl;
             for (auto [id, s] : stantii)
                 cout << s;
            break;
        }
        case 4: {
            if (truby.size() == 0)
                cout << endl << "Трубы не созданы" << endl;
            else {
                cout << endl << "Введите id трубы: ";
                int id;
                id=getInt();
                truby[id].changePipe();
            }
            break;
        }
        case 5: {
            if (stantii.size() == 0)
                cout << endl << "Станция не создана." << endl;
            else {
                cout << endl << "Введите id стации: ";
                int id;
                id = getInt();
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
            cout << "Сохранено!" << endl;
            break;
        }
        case 7: {
            loadAll(truby, stantii);
            cout << "Загружено!" << endl;
            break;
        }
        case 8: {
            bool vremonte=true;
            vector <int> TR= findObject(truby, checkRem, vremonte);
            if (TR.size() == 0) {
                cout << "Все трубы в работе" << endl;
                break;
            }
            else {
            for (int i : TR) cout << truby[i];
            int com2;
            cout << "0.Выход\n1.Удалить трубы \n2.Запустить трубы\n";
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
                cout << "Нет такой команды.\n";
                break;
            }
            }
            }
            break;
        }
        case 9: {
            int perCehNrab;
            cout << "Введите процент нерабочих цехов: ";
            perCehNrab=getInt();
            for (int i :findObject(stantii, checkCehNrab, perCehNrab))
                cout << stantii[i];
            break;
        }
        
        case 10: {
            string name = "";
            do {
                cout << "Введите название станции (на английском):";
                getline(cin >> ws, name);

            } while (cin.fail());
            for (int i : findObject(stantii, checkName, name))
                cout << stantii[i];
            break;
        }
        default: {
            cout << "Нет такой команды.\n";
            break;
        }
        
        }
        cout << "________________________________" <<endl;
        
    }
}






