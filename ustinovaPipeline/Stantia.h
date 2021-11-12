#pragma once
#include <string>
#include <fstream>
#include <iostream>
using namespace std;
class Stantia
{
public:
    int id;
    string name;
    int ceh;
    int cehRab;
    int eff;
    friend std::ostream& operator<< (std::ostream& out, const Stantia& stan);
    static int maxId;
    Stantia(int id);
    Stantia();
    ~Stantia();
    void changeStan();
    static Stantia loadStantia(ifstream& fin);
};

