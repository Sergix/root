#ifndef _ROOTPKG
#define _ROOTPKG

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "in.h"
#include "out.h"
#include "parse.h"

int pkgInstall (string _pkgname, ofstream* _log);
int pkgUninstall (string _pkgname, ofstream* _log);
int pkgSearch (string _pkgname, ofstream* _log);
int pkgInfo (string _pkgname, ofstream* _log);

#endif // _ROOTPKG
