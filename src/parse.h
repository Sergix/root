#ifndef _ROOTPARSE
#define _ROOTPARSE

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <map>

#include "out.h"
#include "edit.h"
#include "exec.h"
#include "pkg.h"

using namespace std;

int parse(string cmd, ofstream* _log, string* _currentdir);

#endif // _ROOTPARSE
