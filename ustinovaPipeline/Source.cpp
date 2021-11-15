#include "Header.h"
#include <iostream>;
using namespace std;

int getInt()
{
    int input;
    while (1) {
        cin >> input;
        if (!cin.fail())
            return input;
        cin.clear();
        cin.ignore(2000, '\n');
    }
}