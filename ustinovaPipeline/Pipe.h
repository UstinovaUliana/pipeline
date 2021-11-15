#pragma once
#include <string>
#include <fstream>
#include <iostream>
using namespace std;
class Pipe
{
    static int maxId;
    public:

    int id;
    double d;
    double l;
    bool rem;
    friend std::ostream& operator<< (std::ostream& out, const Pipe& pipe);
 

    Pipe& CreatePipe(Pipe& p);
    Pipe();
    ~Pipe();
    void changePipe();
    static Pipe& loadPipe(ifstream& fin, Pipe& pipe);
};

