

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
        cout << "Введите диаметр трубы, мм:";
        cin >> truba.d;
    } while (cin.fail() || truba.d < 50 || truba.d>2000);
     do {
         cin.clear();
         cin.ignore(2000, '\n');
        cout << "Введите длину трубы, км:";
        cin >> truba.l;
     } while (cin.fail() || truba.l < 0.05 || truba.l>100);
    
    return truba;
}

Stantia createStantia() {
    Stantia stan;
    stan.id = 2;
    do {
        cout << "Введите название станции (на английском):";
        cin >> stan.name;
    } while (cin.fail());
    
    do {
        cin.clear();
        cin.ignore(2000, '\n');
        cout << "Введите количество цехов:";
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
    cout << "Труба" << endl << "Id: " << truba.id << endl << "Диаметр: " << truba.d << "мм" << endl << "Длина: " << truba.l << "км" << endl << "В ремонте: ";
    if (truba.rem) { cout << "да"; }
    else { cout << "нет"; }
    cout << endl;
}
void coutStantia(Stantia& stan)
{
    cout << "Станция" << endl << "Id: " << stan.id << endl << "Название: " << stan.name << endl << "Кол-во цехов " << stan.ceh << endl << "Цехов в работе: " << stan.cehRab << endl << "Эффективность: " << stan.eff << endl;
}

void savePipe(Pipe& truba)
{
    ofstream fout;
    fout.open("OutTruba.txt", ios::out);
    if (fout.is_open()) {
        fout << "Труба" << endl << "Id: " << truba.id << endl << "Диаметр: " << truba.d << "мм" << endl << "Длина: " << truba.l << "км" << endl << "В ремонте: ";
        if (truba.rem) { fout << "да"; }
        else { fout << "нет"; }
        fout << endl;
        fout.close();
    }
    
}
void saveStantia(Stantia& stan)
{
    ofstream fout;
    fout.open("OutStantia.txt", ios::out);
    if (fout.is_open()) {
        fout << "Станция" << endl << "Id: " << stan.id << endl << "Название: " << stan.name << endl << "Кол-во цехов " << stan.ceh << endl << "Цехов в работе: " << stan.cehRab << endl << "Эффективность: " << stan.eff << endl;
        fout.close();
    }
    
}

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << " 1. Добавить трубу \n 2. Добавить КС \n 3. Просмотр всех объектов \n 4. Редактировать трубу \n 5. Редактировать КС \n 6. Сохранить \n 7. Загрузить \n 0. Выход \n";
    int com;
    int oldCehRab;
    bool trubaExist = false;
    bool stanExist = false;
    Pipe truba;
    Stantia stan;
    cout << "Команда: ";
    cin >> com;
    
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
                cout << "Ничего не создано" << endl;
            }
            break;
        }
        case 4: {
            if (!trubaExist) {
                cout << "Труба не создана" << endl;
            }
            else {
                truba.rem = true;
                coutPipe(truba);
            }
            break;
        }
        case 5: {
            if (!stanExist) {
                cout << "Станция не создана" << endl;
            }
            else {
                oldCehRab = stan.cehRab;
                if (stan.cehRab >= 1) {
                    stan.cehRab = stan.cehRab - 1;
                }
                else { stan.cehRab = stan.cehRab; };
                stan.eff = stan.cehRab*100/oldCehRab;
                coutStantia(stan);
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
                cout << "Ничего не создано" << endl;
            }
            cout << "Сохранено!";
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
            cout << "Вводите цифру.\n";
            break;
        }*/
        default: {
            cout << "Нет такой команды.\n";
            break;
        }
        
        }
        
        cout << "Команда: ";
        cin >> com;
    }
}
    //+цехи по вводу
    //в название водятся несколько слов
    //+переменную а убрать, сделать кейсы
    //+нецелые числа чтобы вводились
    //+если число 0, ритурн брейк, если другие, "нет такой команды"
    //+некорректный ввод чисел 
    //+чтение из файла, ввод в файл
    //проверка ввода имени
    // меню и редактирование - операции
// проверка ввода команды
   




