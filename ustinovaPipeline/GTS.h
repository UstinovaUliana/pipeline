#pragma once
#include <unordered_map>
#include <map>
#include "Pipe.h"
#include "Stantia.h"
#include <string>
#include "Node.h"
#include "Verge.h"
class GTS
{
public:
    unordered_map <int, Pipe> truby;
    unordered_map <int, Stantia> stantii;
    struct pairCS {
        int fromCSid;
        int toCSid;
    };
    map <int, pairCS> CPC;
    void connectPipe(Stantia& sout, Pipe& p, Stantia& sin);
    void disconnectPipe(Stantia& sout, Pipe& p, Stantia& sin);
    vector <vector <int>> matrSmezh;
    map <int, Stantia> sort(unordered_map<int, Stantia> stantii);
    vector <vector<int>> makeMatrSmezh(unordered_map<int, Stantia> stantii, unordered_map<int, Pipe> truby);
    unordered_map<int, Node> toNodesMap(const unordered_map<int, Stantia>& stationsMap);

    unordered_map<int, Verge> toVergesMap(const unordered_map<int, Pipe>& pipesMap);
    void findMinWay(unordered_map<int, Node> nodesMap, unordered_map<int, Verge> vergeMap, int startID);
    int potok(unordered_map<int, Stantia> stantii, unordered_map<int, Pipe> truby);
};

