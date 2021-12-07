#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <set>
class Stantia
{

    int id;
public:
    string name;
    int ceh;
    int cehRab;
    int eff;
    set <int> PipIn;
    set <int> PipOut;
    /*
    vector <int> conPipes;*/

    int getId() { return id; };
    static int maxId;
    friend std::ostream& operator<< (std::ostream& out, const Stantia& stan);
    friend std::istream& operator>> (std::istream& in, Stantia& s);
    friend std::ifstream& operator>> (std::ifstream& fin, Stantia& s);
    friend std::ofstream& operator<< (std::ofstream& out, Stantia& s);
    Stantia();
    void changeStan();
};

