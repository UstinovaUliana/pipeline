

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
    cout << "Введите диаметр трубы, мм:";
    cin >> truba.d;
    cout << "Введите длину трубы, км:";
    cin >> truba.l;
    return truba;
}

Stantia createStantia() {
    Stantia stan;
    stan.id = 2;
    cout << "Введите название станции (на английском):";
    cin >> stan.name;
    cout << "Введите количество цехов:";
    cin >> stan.ceh;
    stan.cehRab = stan.ceh;
    stan.eff = 100;
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
            cout << "Нет такой команды.\n";
            break;
        }
        }
        cout << "Команда: ";
        cin >> com;
        if (!cin) {
            cin.clear();
            cin.ignore(100);
            cout << "Вводите номер команды.";
        }
    }
}
    //+цехи по вводу
    //в название водятся несколько слов
    //если в название вводить цифры, тебя поправляют (и наоборот)
    //+переменную а убрать, сделать кейсы
    //+нецелые числа чтобы вводились
    //+если число 0, ритурн брейк, если другие, "нет такой команды"
    //некорректный ввод чисел 
    //чтение из файла, ввод в файл
   




