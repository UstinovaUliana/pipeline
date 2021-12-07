#pragma once
#include <string>
#include <fstream>
#include <iostream>
using namespace std;
class Pipe
{
    int id;
  public:
    static int maxId;
    double d;
    double l;
    bool rem;
    int idOut;
    int idIn;
    int getId() { return id; };
    friend std::ifstream& operator>> (std::ifstream& fin, Pipe& pipe);
    friend std::istream& operator>> (std::istream& out, Pipe& p);
    friend std::ostream& operator<< (std::ostream& out, const Pipe& pipe);
    friend std::ofstream& operator<< (std::ofstream& out, const Pipe& pipe);
 
    Pipe();
    void changePipe();
};

