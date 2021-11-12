#include <iostream>
#include <locale.h>
#include <string>
#include <fstream>
#include "ustinovaPipeline.h"
#include "Pipe.h"
#include "Stantia.h"
#include <unordered_map>
using namespace std;

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
    Pipe::maxId = 0;
    Stantia::maxId = 0;
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
                truby.emplace(Pipe::maxId+1, Pipe::loadPipe(fin));
            }
            if (type == "Stantia") {
                stantii.emplace(Stantia::maxId+1, Stantia::loadStantia(fin));
            }
        }
        fin.close();
    }
    else cout << "Не открывается." << endl;
}
void menu()
{
    cout << " 1. Добавить трубу \n 2. Добавить КС \n 3. Просмотр всех объектов \n 4. Редактировать трубу \n 5. Редактировать КС \n 6. Сохранить \n 7. Загрузить \n 8. Поиск труб в ремонте \n 9. Поиск станций по проценту нерабочих цехов (больше введённого) \n 10. Отредактировать несколько труб \n 11.Удалить трубу\n 12.Удалить КС\n 0. Выход \n";
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
template<typename T, typename Obj>

vector<int> findObject(const unordered_map<int, Obj>& object, filter<T,Obj> f, T param)
{
    vector<int> found;
    for (auto [id,p] : object)
    {
        if (f(p, param))
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
            truby.emplace( Pipe::maxId, Pipe(Pipe::maxId+1));
            cout<< truby[Pipe::maxId]<<endl;
            break;
        }
        case 2: {
            stantii.emplace(Stantia::maxId+1, Stantia(Stantia::maxId+1));
            cout << stantii[Stantia::maxId+1] << endl;
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
            for (int i :findObject(truby, checkRem, vremonte))
                cout << truby[i];
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
            if (truby.size() == 0)
                cout << endl << "Трубы не созданы" << endl;
            else {
                cout << endl << "Количество изменяемых труб: ";
                int kolvo = getInt();
                vector<int> trubyChange;
                for (int i = 1; i <= kolvo; i++)
                {
                    cout << endl << "Введите id трубы: ";
                    int id = getInt();
                    trubyChange.push_back(id);
                    
                }
                for (int i:trubyChange)
                truby[i].changePipe();
            }
            break;
        }
        case 11: {
            cout << endl << "Введите id трубы: ";
            int id = getInt();
            truby.erase(id);
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
//+-проверка ввода
//удаление труб и станций
//трубы в ремонте - удалить/запустить
//поиск станций по имени - разные имена





