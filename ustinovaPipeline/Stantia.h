#pragma once
#include <string>
#include <fstream>
#include <iostream>
using namespace std;
class Stantia
{
    static int maxId;
public:
    int id;
    string name;
    int ceh;
    int cehRab;
    int eff;
    friend std::ostream& operator<< (std::ostream& out, const Stantia& stan);
  
    Stantia& CreateStantia(Stantia& s);
    Stantia();
    ~Stantia();
    void changeStan();
    static Stantia& loadStantia(ifstream& fin, Stantia& s);
};

