#pragma once
#include <string>
#include <fstream>
#include <iostream>
using namespace std;
class Pipe
{
    public:

    int id;
    double d;
    double l;
    bool rem;
    friend std::ostream& operator<< (std::ostream& out, const Pipe& pipe);
    static int maxId;

    Pipe(int id);
    Pipe();
    ~Pipe();
    void changePipe();
    static Pipe loadPipe(ifstream& fin);
};

