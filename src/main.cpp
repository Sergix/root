/*
    root v1.1 - A more accessible, portable windows terminal with package integration.
    Copyright (C) 2017 Sergix

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    
    For any questions or information concerning this product, e-mail to
    "sergix@outlook.com".
   */

#include "boot.h"
#include "parse.h"

using namespace std;

int main()
{
    // Initialize global vars


    // Initialize local vars
    int _install;
    string _currentdir = "/root/user/home";
    string _prompt = _currentdir + (string)">";
    string _cmd;

    // Set up log file
    ofstream _log("native.log", ios_base::out);

    // Look for the installation and call functions located in sys.h
    log("Searching for installation...", &_log);

    // Check for return values for different function call based on boot preference
    _install = searchInstall(&_log);

    if(_install == 1)
        install(&_log);
    else if(_install == 0)
        _install = login(&_log);

    // If login failed, exit program
    if(_install == 1)
        return 0;

    // Switch log output to userlog.log
    logf("Switching log file to userlog", &_log);
    ofstream _userlog("/root/user/logs/userlog.log", ios_base::app);
    logf("\nLoaded log file", &_userlog);

    // Clear the screen
    system("cls");
    system("cd /root/user/home");

    // Endless loop of command parsing
    do
    {
        prompt(&_cmd, _currentdir + ">");
        logf(_currentdir + ">" + _cmd, &_userlog);
        parse(_cmd, &_log, &_currentdir);
        logf("", &_userlog); // place a newline
    } while (_cmd != (string)"sd");
    // FIX ABOVE LINE
    // ex: "sd 123" does not exit loop; "sd" /= "sd 123"
    //

    // Shutdown the system
    log("Closing ROOT...", &_userlog);

    return 0;
}
