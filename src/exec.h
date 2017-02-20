#ifndef _ROOTEXEC
#define _ROOTEXEC

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

#include "parse.h"

int exec(string _filename, ofstream* _log, string* _currentdir);
int execparse(istringstream* _stream, ifstream* _exec, map<string, string>* _vars, map<string, fstream*>* _files, ofstream* _log, string* _currentdir);

#endif // _ROOTEXEC
