#ifndef _ROOTIN
#define _ROOTIN

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int wait();

template <class C> int prompt(C* _input, string _prompt)
{
    cout << _prompt;
    getline(cin, *_input);
    cout << endl;
    return 0;
}

#endif // _ROOTIN
