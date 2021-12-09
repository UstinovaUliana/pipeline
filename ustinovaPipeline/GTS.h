#pragma once
#include <unordered_map>
#include <map>
#include "Pipe.h"
#include "Stantia.h"
#include <string>
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
    void connectPipe(Stantia sout, Pipe p, Stantia sin);
    void disconnectPipe(Stantia sout, Pipe p, Stantia sin);
    vector <vector <int>> matrSmezh;
};

