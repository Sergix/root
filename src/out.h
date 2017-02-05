#ifndef _ROOTOUT
#define _ROOTOUT

#include <iostream>
#include <fstream>
#include <cstring>
#include <windows.h>

using namespace std;

template <class C> int log(C text, ofstream* file)
{
    cout << text << endl;
    *file << text << endl;

    return 0;
}

template <class C> int logf (C text, ofstream* file)
{
    *file << text << endl;

    return 0;
}

#endif // _ROOTOUT
