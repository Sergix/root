#ifndef _ROOTINIT
#define _ROOTINIT

#include <iostream>
#include <fstream>
#include <cstdio>
#include <map>
#include <windows.h>

#include "in.h"
#include "out.h"

using namespace std;

int searchInstall(ofstream* log);
int login(ofstream* _log);
int install(ofstream* _log);

#endif // _ROOTINIT
