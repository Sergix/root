#ifndef _ROOTLIB
#define _ROOTLIB 1

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <windows.h>

#include "out.h"
#include "in.h"

int log (const char* text, ofstream* file);
int log (string text, ofstream* file);
int logf (const char* text, ofstream* file);

int prompt(char* input);
int prompt(char* input, char* prompt);
int prompt(string* input, const char* prompt);

#endif
