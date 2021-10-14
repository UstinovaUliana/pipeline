

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
   
    out << "Труба" << endl << "Id: " << truba.id << endl << "Диаметр: " << truba.d << "мм" << endl << "Длина: " << truba.l << "км" << endl << "В ремонте: ";
    if (truba.rem) { out << "да"; }
    else { out << "нет"; }
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

    out << "Станция" << endl << "Id: " << stan.id << endl << "Название: " << stan.name << endl << "Кол-во цехов: " << stan.ceh << endl << "Цехов в работе: " << stan.cehRab << endl << "Эффективность: " << stan.eff << endl;


    return out;
}

int  tc = 0;
int sc = 0;
Pipe createPipe() {
    Pipe truba;
    truba.id = tc++;
    truba.rem = false;
    do {
        cin.clear();
        cin.ignore(2000, '\n');
        cout << "Введите диаметр трубы, мм (50-2000):";
        cin >> truba.d;
    } while (cin.fail() || truba.d < 50 || truba.d>2000);
     do {
         cin.clear();
         cin.ignore(2000, '\n');
        cout << "Введите длину трубы, км (0.05-10000):";
        cin >> truba.l;
     } while (cin.fail() || truba.l < 0.05 || truba.l>10000);
    
    return truba;
}

Stantia createStantia() {
    Stantia stan;
    stan.id = sc++;
    do {
        cout << "Введите название станции (на английском) и дважды нажмите Enter:";
        getline(cin>>ws, stan.name);
  
    } while (cin.fail());
    
    do {
        cin.clear();
        cin.ignore(2000, '\n');
        cout << "Введите количество цехов (1-10):";
        cin >> stan.ceh;
    } while (cin.fail() || stan.ceh < 1 || stan.ceh>10);
    stan.cehRab = 1;
    stan.eff = 100*stan.cehRab/stan.ceh;
    do {
        cin.clear();
        cin.ignore(2000, '\n');
        cout << "Введите эффективность: ";
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
    cout << "Труба" << endl << "Id: " << truba.id << endl << "Диаметр: " << truba.d << "мм" << endl << "Длина: " << truba.l << "км" << endl << "В ремонте: ";
    if (truba.rem) { cout << "да"; }
    else { cout << "нет"; }
    cout << endl;
}
void coutStantia(Stantia& stan)
{
    cout << "Станция" << endl << "Id: " << stan.id << endl << "Название: " << stan.name << endl << "Кол-во цехов: " << stan.ceh << endl << "Цехов в работе: " << stan.cehRab << endl << "Эффективность: " << stan.eff << endl;
}

void saveAll(Pipe& truba, Stantia& stan)
{
    ofstream fout;
    cout << "Введите название файла: ";
    string ofileName;
    cin >> ofileName;
    fout.open(ofileName+".txt", ios::out);
    if (fout.is_open()) {
        fout << truba.id << endl << truba.d << endl << truba.l << endl << truba.rem;
        fout << endl;
        fout << stan.id << endl << stan.name << endl << stan.ceh << endl << stan.cehRab << endl << stan.eff << endl;
        fout.close();
    }
    
}

void menu()
{
    cout << " 1. Добавить трубу \n 2. Добавить КС \n 3. Просмотр всех объектов \n 4. Редактировать трубу \n 5. Редактировать КС \n 6. Сохранить \n 7. Загрузить \n 0. Выход \n";
}

void changePipe(Pipe& truba)
{
    truba.rem = !truba.rem;
    cout << truba;

}
void changeStan(Stantia& stan)
{  
    cout << "Введите кол-во рабочих цехов: ";
    cin >> stan.cehRab;
    while (stan.cehRab > stan.ceh || stan.cehRab < 0) {
        cin.clear();
        cin.ignore(2000, '\n');
        cout << "Введите кол-во рабочих цехов: ";
        cin >> stan.cehRab;
    }
    coutStantia(stan);
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
            coutPipe(truba);
            break;
        }
        case 2: {
            stan = createStantia();
            stantii.insert({ sc, stan });
            coutStantia(stan);
            break;
        }
        case 3: {
            if (truby.size()==0)
                cout << "Трубы не созданы" << endl;
            for (auto [id, p] : truby)
                cout << p;
             if (stantii.size()==0)
                 cout << "Станции не созданы" << endl;
             for (auto [id, s] : stantii)
                 cout << s;
            break;
        }
        case 4: {
            if (truby.size() == 0)
                cout << "Трубы не созданы" << endl;
            else {
                cout << "Введите id трубы: ";
                //проверка
                int id;
                cin >> id;

                changePipe(truby[id]);
            }
            break;
        }
        case 5: {
            if (stantii.size() == 0)
                cout << "Станция не создана" << endl;
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
            if (stantii.size() == 0)
                stan = {};
            if (truby.size()==0) 
                truba = {};
            
            saveAll(truba, stan);
            /*if (trubaExist) {
                saveAll(truba,stan);
            }
            if (stanExist) {
                saveAll(stan);
            }
            else {
                cout << "Ничего не создано" << endl;
            }*/

            cout << "Сохранено!" << endl;
            break;
        }
        case 7: {

            ifstream fin;
            cout << "Введите название файла: ";
            string ifileName;
            cin >> ifileName;
            fin.open(ifileName+".txt", ios::in);
            if (!fin.is_open())
            {
                cout<<"Не открывается."<<endl;
                break;
            }
            truba = loadPipe(fin);
            stan = loadStantia(fin);
            fin.close();

            break;
        }
        /*if (cin.fail()) {
            cout << "Вводите цифру.\n";
            break;
        }*/
        default: {
            cout << "Нет такой команды.\n";
            break;
        }
        
        }

        
    }
}
    //+цехи по вводу
    //+в название водятся несколько слов
    //+переменную а убрать, сделать кейсы
    //+нецелые числа чтобы вводились
    //+если число 0, ритурн брейк, если другие, "нет такой команды"
    //+некорректный ввод чисел 
    //+чтение из файла, ввод в файл
    //+меню и редактирование - операции
    //+проверка ввода команды
    // 
//проверка ввода
//сохранение и загрузка

   




