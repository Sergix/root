#include "boot.h"

using namespace std;

int searchInstall(ofstream* log)
{
    char _debug[5];
    char _reset[5];

    logf<string>("Checking for boot initialization file...", log);
    ifstream _exist("/root/boot");

    if(!_exist)
    {
        _exist.close();
        logf("boot file does not exist", log);
        return 1;
    }

    _exist.seekg(21, ios_base::beg);
    _exist.getline(_debug, 5);

    if(strcmp(_debug, "true") == 0)
        return 2;

    _exist.seekg(14, ios_base::cur);
    _exist.getline(_reset, 5);
    _exist.close();

    if(strcmp(_reset, "true") == 0)
        return 1;

    logf("File exists, continuing as normal...", log);
    return 0;
}

int login(ofstream* _log)
{
    // Local var initialization
    char _username[80];
    char _password[80];
    string __username;
    string __password;
    string _message;

    log("Loading user...", _log);

    // Get username and password values
    ifstream _userdata("/root/user/data/userdata", ios_base::in);
    _userdata.seekg(9, ios_base::beg);
    _userdata.getline(_username, 80);
    _userdata.seekg(9, ios_base::cur);
    _userdata.getline(_password, 80);

    logf("Requesting authorization from user...", _log);
    prompt(&__username, "Enter user name>");
    prompt(&__password, "Enter password>");

    if(__username != _username || __password != _password)
    {
        log("Verification failed!", _log);
        return 1;
    }

    _message = (string)"\nWelcome back, " + (string)_username + (string)"! (Enter any key to continue)\n";
    log(_message, _log);

    //wait();

    return 0;
}

int install(ofstream* _log)
{
    string _username;
    string _password;
    string _install;

    logf("Requesting permission to install system...", _log);
    prompt(&_install, "Install ROOT? [Y/N]");
    if(_install == "N")
    {
        logf("Authorization failed", _log);
        log("Canceling installation...", _log);
        return 1;
    }

    logf("Creating directories", _log);

    logf("- /root", _log);
    CreateDirectory("/root", NULL);

    logf("- /root/bin", _log);
    CreateDirectory("/root/bin", NULL);

    logf("- /root/bin/sys", _log);
    CreateDirectory("/root/bin/sys", NULL);

    logf("- /root/bin/sys/drv", _log);
    CreateDirectory("/root/bin/sys/drv", NULL);

    logf("- /root/bin/lib", _log);
    CreateDirectory("/root/bin/lib", NULL);

    logf("- /root/pkg", _log);
    CreateDirectory("/root/pkg", NULL);

    logf("- /root/user", _log);
    CreateDirectory("/root/user", NULL);

    logf("- /root/user/home", _log);
    CreateDirectory("/root/user/home", NULL);

    logf("- /root/user/pkgdata", _log);
    CreateDirectory("/root/user/pkgdata", NULL);

    logf("- /root/user/logs", _log);
    CreateDirectory("/root/user/logs", NULL);

    logf("- /root/user/data", _log);
    CreateDirectory("/root/user/data", NULL);

    logf("Creating boot file", _log);
    ofstream _boot("/root/boot", ios_base::out);
    _boot << "[PARAMS]\ndebug-mode=false\nreset-install=false";
    _boot.close();

    prompt(&_username, "Enter new user name >");
    prompt(&_password, "Enter new password  >");

    logf("Setting user data file parameters...", _log);
    ofstream _userdata("/root/user/data/userdata", ios_base::out);
    _userdata << "username=" << _username << "\npassword=" << _password;
    _userdata.close();

    logf("Creating package list file...", _log);
    ofstream _pkglist("/root/user/pkgdata/pkglist", ios_base::out);
    _pkglist.close();

    log("Installation finished!", _log);

    return 0;
}
