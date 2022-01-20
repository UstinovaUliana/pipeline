#include "GTS.h"
#include <unordered_set>
#include <iterator>
void GTS::connectPipe(Stantia& sout, Pipe& p, Stantia& sin ) {
    p.idOut = sout.getId();
    p.idIn = sin.getId();
    sout.PipOut.emplace(p.getId());
    sin.PipIn.emplace(p.getId());

}
void GTS::disconnectPipe(Stantia& sout, Pipe& p, Stantia& sin) {
    sout.PipOut.erase(p.getId());
    sin.PipIn.erase(p.getId());
    p.idOut = 0;
    p.idIn = 0;
    
}
map <int, Stantia> GTS::sort(unordered_map<int, Stantia> stantii) {
    map <int, Stantia> sortResults;
    int sortNum = 0;
    vector <int> sToChange;

    int counter = 0;
    int kolvoStan = stantii.size();
    while (sortResults.size() != kolvoStan) {
        sToChange.clear();
        for (auto [id, s] : stantii) {
            if (s.PipIn.size() == 0) {
                sToChange.push_back(id);
            }
        }
        for (int i : sToChange) {
            sortNum++;
            sortResults[sortNum] = stantii[i];
            for (auto j : stantii[i].PipOut) {
                for (auto& [id, s1] : stantii) {
                    s1.PipIn.erase(j);
                }
            }
        }
        for (auto i : sToChange)
            stantii.erase(i);
        /*cout << ++counter << " Action, ";
        for (int i : sToChange) {
            cout << "ID: " << i << std::endl;
        }*/

        if (sToChange.size() == 0) {
            cout << "В графе есть цикл. " << endl;
            sortResults.clear();
            break;
        }

        return sortResults;
    }
}

vector <vector<int>> GTS::makeMatrSmezh(unordered_map<int, Stantia> stantii, unordered_map<int, Pipe> truby) {
    vector <vector<int>> matrSmezh;
    matrSmezh.resize(stantii.size()+1);
    for (int i = 1; i < matrSmezh.size(); ++i)
        matrSmezh[i].resize(stantii.size()+1);
    map <int, Stantia> SwithNum;
    map <int, int> numFromId;
    int numOfS = 0;
    for (auto [id, s] : stantii) {
        numOfS++;
        SwithNum.emplace(numOfS, s);
        numFromId.emplace(id, numOfS);
    }
      for (auto [num, s] : SwithNum) {
        for (int idp : s.PipOut)
            matrSmezh[num][numFromId[truby[idp].idIn]] = truby[idp].l;
    }
    return matrSmezh;
}
unordered_map<int, Node> GTS::toNodesMap(const unordered_map<int, Stantia>& stationsMap) {
    unordered_map<int, Node> nodesMap;

    for (auto& item : stationsMap) {
        nodesMap.insert({ item.first, Node(item.second.PipIn.size(), item.second.PipOut.size(), INT_MAX) });
    }

    return nodesMap;
}

unordered_map<int, Verge> GTS::toVergesMap(const unordered_map<int, Pipe>& pipesMap) {
    unordered_map<int, Verge> vergeMap;
    for (auto& item : pipesMap) {
        vergeMap.insert({ item.first, Verge(item.second.idOut, item.second.idIn, item.second.l, !(item.second.rem) )});
    }

    return vergeMap;
}
void GTS::findMinWay(unordered_map<int, Node> nodesMap, unordered_map<int, Verge> vergeMap, int startID) {
    set<int> setOfChangableNodes;
    map <int, vector<int>> ways;
    nodesMap[startID].weight = 0;
    int curid = startID;
        for (auto& verge: vergeMap)
            if (verge.second.startID == curid && verge.second.isWorking) {
                setOfChangableNodes.insert(verge.second.endID);
                ways.emplace(verge.second.endID, 0);
            }

    int workID = startID;
    while (setOfChangableNodes.size() != 0) {
        // change verges
        for (auto& item : vergeMap) {
            if (item.second.startID == workID
                && item.second.isWorking
                && nodesMap[item.second.startID].weight + item.second.length < nodesMap[item.second.endID].weight) {

                nodesMap[item.second.endID].weight = nodesMap[item.second.startID].weight + item.second.length;
                ways[item.second.endID].push_back(item.second.startID);
            }
        }
        setOfChangableNodes.erase(workID);

        int min = INT_MAX;
        // find next node
        for (int i : setOfChangableNodes) {

            if (setOfChangableNodes.size() == 1) workID = i;
            if (nodesMap[i].weight < min) {
                min = nodesMap[i].weight;
                workID = i;

            }
        }
    }

    /*
        for (auto& node : nodesMap) {
        for (auto& verge : vergeMap ) {
            if ((verge.second.endID == node.first )&& (node.second.weight == nodesMap[verge.second.startID].weight - verge.second.length)) {
                ways[node.first].push_back(verge.second.startID);
            }
        }
    }*/

    
    for (auto& item1 : nodesMap) {
        for (auto i : ways[item1.first]) {
            for (auto& item2 : nodesMap) {
                for (auto j: ways) {
                    if (ways[item1.first][1] == j.first)
                     for (auto k: ways[item2.first]) ways[item1.first].push_back(k);
                }
            }
        }
    }
    /*for (auto& item : nodesMap) {
        for (auto i : ways[item.first]) {
            ways[item.first].push_back(item.first);
        }
    }*/
    for (auto& item : nodesMap) {
        std::cout << "Id станции: " << item.first << std::endl;
        if (item.second.weight>=200000 or item.second.weight <0)   std::cout << "Нет пути." <<endl;
        else std::cout << "Длина пути: " << item.second.weight << std::endl;
        for (auto i: ways[item.first]) {
            std::cout << i << "-->";
        }
        std::cout<< item.first;
        std::cout << endl;
    }
}
    //    vector<int> parent(5, -1);
    //    int big_num(10000);
    //    int matrix[5][5];
    //    for (int i = 1; i < MS.size(); i++)
    //    {
    //        for (int j = 1; j < MS[i].size(); j++) {
    //            matrix[i][j] = MS[i][j];
    //            cout << matrix[i][j]<<" ";
    //        }
    //        cout << endl;
    //    }
    //    map <int, int> numFromId;
    //    int numOfS = 0;
    //    for (auto [id, s] : stantii) {
    //        numOfS++;
    //        numFromId.emplace(id, numOfS);
    //    }
    //    int pos[5], node[5], min(0), index_min(0);
    //    for (int i = 0; i < 5; ++i) {
    //        pos[i] = big_num;
    //        node[i] = 0;
    //    }
    //
    //    pos[numFromId[stanIdFrom]] = 0;            // наш узел
    //    cout << "\n";
    //    for (int i = 0; i < 4; ++i) {
    //        min = big_num;
    //        for (int j = 0; j < 5; ++j) {
    //            if (!node[j] && pos[j] < min) {
    //                min = pos[j];
    //                index_min = j;
    //            }
    //        }
    //        node[index_min] = true;
    //        for (int j = 0; j < 5; ++j) {
    //            if (!node[j] && matrix[index_min][j] > 0 && pos[index_min] != big_num && pos[index_min] + matrix[index_min][j] < pos[j]) {
    //                pos[j] = pos[index_min] + matrix[index_min][j];
    //                parent.at(j) = index_min;    // запоминаем предка вершины j
    //            }
    //        }
    //    }
    //    int n(0);
    //    n = stanIdTo;
    //
    //    vector<int>temp;     // n - 1, так как не забываем про индексацию
    //    for (int i = n - 1; i != -1; i = parent.at(i))temp.push_back(i + 1);   // а все что здесь делается  описано в справке,которую я те кинул
    //    reverse(temp.begin(), temp.end());
    //    for (int i = 0; i < temp.size(); ++i)cout << temp.at(i) << " ";
    //
    //    cout << "\nWeight : " << pos[n - 1] << "\n";
    //
    //    cout << endl;
    //    cout << pos[numFromId[stanIdTo]];
    //    cout << endl;
    //    for (int i = 1; i < 4; i++) {
    //
    //        cout << i << ": " << pos[i] << endl;
    //    }
    //}
        //int d[5]; // минимальное расстояние
        //int v[5]; // посещенные вершины
        //int temp, minindex, min;
        //int begin_index = 0;
        //system("chcp 1251");
        //system("cls");
        //map <int, Stantia> SwithNum;
        //map <int, int> numFromId;
        //int numOfS = 0;
        //for (auto [id, s] : stantii) {
        //    numOfS++;
        //    SwithNum.emplace(numOfS, s);
        //    numFromId.emplace(id, numOfS);
        //}
        ////Инициализация вершин и расстояний
        //for (int i = 0; i < 5; i++)
        //{
        //    d[i] = 10000;
        //    v[i] = 1;
        //}
        //d[begin_index] = numFromId[stanIdFrom];
        //// Шаг алгоритма
        //do {
        //    minindex = 10000;
        //    min = 10000;
        //    for (int i = 0; i < 5; i++)
        //    { // Если вершину ещё не обошли и вес меньше min
        //        if ((v[i] == 1) && (d[i] < min))
        //        { // Переприсваиваем значения
        //            min = d[i];
        //            minindex = i;
        //        }
        //    }
        //    // Добавляем найденный минимальный вес
        //    // к текущему весу вершины
        //    // и сравниваем с текущим минимальным весом вершины
        //    if (minindex != 10000)
        //    {
        //        for (int i = 0; i < 5; i++)
        //        {
        //            if (MS[minindex][i] > 0)
        //            {
        //                temp = min + MS[minindex][i];
        //                if (temp < d[i])
        //                {
        //                    d[i] = temp;
        //                }
        //            }
        //        }
        //        v[minindex] = 0;
        //    }
        //} while (minindex < 10000);
        //// Вывод кратчайших расстояний до вершин
        //printf("\nКратчайшие расстояния до вершин: \n");
        //for (int i = 0; i < 5; i++)
        //    printf("%5d ", d[i]);
        //const int SIZE = 5;
        //// Восстановление пути
        //int ver[SIZE]; // массив посещенных вершин
        //int end = numFromId[stanIdTo]; // индекс конечной вершины = 5 - 1
        //ver[0] = end + 1; // начальный элемент - конечная вершина
        //int k = 1; // индекс предыдущей вершины
        //int weight = d[end]; // вес конечной вершины

        //while (end != begin_index) // пока не дошли до начальной вершины
        //{
        //    for (int i = 0; i < SIZE; i++) // просматриваем все вершины
        //        if (MS[i][end] != 0)   // если связь есть
        //        {
        //            int temp = weight - MS[i][end]; // определяем вес пути из предыдущей вершины
        //            if (temp == d[i]) // если вес совпал с рассчитанным
        //            {                 // значит из этой вершины и был переход
        //                weight = temp; // сохраняем новый вес
        //                end = i;       // сохраняем предыдущую вершину
        //                ver[k] = i + 1; // и записываем ее в массив
        //                k++;
        //            }
        //        }
        //}
        //// Вывод пути (начальная вершина оказалась в конце массива из k элементов)
        //printf("\nВывод кратчайшего пути\n");
        //for (int i = k - 1; i >= 0; i--)
        //    printf("%3d ", ver[i]);
        //getchar(); getchar();
        /*vector <vector<int>> way;
        map <int, Stantia> SwithNum;
        map <int, int> numFromId;
        int numOfS = 0;
        for (auto [id, s] : stantii) {
            numOfS++;
            SwithNum.emplace(numOfS, s);
            numFromId.emplace(id, numOfS);
        }
        int counter=0;
        for (int i = 1; i < matrSmezh[numFromId[stanIdFrom]].size(); i++) {
            if (matrSmezh[numFromId[stanIdFrom]][i] != 0) {
                way[counter++].push_back(i);
                if (i == numFromId[stanIdTo]) break;
            }
        }
        int counter = 0;
        for (auto j : way) {
            for (int i = 1; i < matrSmezh[numFromId[stanIdFrom]].size(); i++) {
                if (matrSmezh[j[counter]][i] != 0) {
                    j.push_back(i);
                }
                if (i == numFromId[stanIdTo]) break;
            }
        }*/
        /*unordered_map<int, Stantia> stantii1;

        for (auto& item : stantii) {
            stantii1.insert({ item.first, Stantia(item.second.PipIn, item.second.PipOut, INT_MAX) });
        }

    unordered_map<int, Verge> Network::toVergesMap(const unordered_map<int, Pipe>&pipesMap) {
        unordered_map<int, Verge> vergeMap;
        for (auto& item : pipesMap) {
            vergeMap.insert({ item.first, Verge(item.second.startID, item.second.endID, item.second.length, item.second.isWorking) });
        }

        return vergeMap;
    }*/

//    int GTS::potok (unordered_map<int, Stantia> stantii, unordered_map<int, Pipe> truby) {
//
//        int stream;
//        int pometka;
//        map <int, Stantia> versh;
//        /*for (auto [id, s] : stantii)
//        {
//            versh.emplace(0, s);
//        }*/
//        std::cout << "Введите id начальной вершины: \n";
//        int startId = getInt();
//        std::cout << "Введите id конечной вершины: \n";
//        int endId = getInt();
//        int rassm = startId;
//        for (int i : ) {
//            for (auto j : stantii[i].PipOut) {
//                  for (auto& [id, s1] : stantii) {
//                 ids=find(s1.PipIn =j);
//          truby[j].perf= sqrt(power(truby[j].d,5)/truby[j].l);
//                  versh[ids].first= min(versh[i].first,versh[--].first - truby[j].perf)
  //              }
//            }
//        }
//}
