#include "pkg.h"

int pkgInstall (string _pkgname, ofstream* _log)
{
    string _dir = "/root/pkg/" + _pkgname + "/host";
    char cmd[2048];
    string _cmd;

    string _name;
    string _exec;
    string _id;

    ofstream _pkglist("/root/user/pkgdata/pkglist", ios_base::app);

    logf("Installing package " + _pkgname, _log);
    log("Looking for package: " + _pkgname, _log);

    ifstream _host(_dir.c_str(), ios_base::in);

    if (!_host)
    {
        log("error: package \"" + _pkgname + "\" not found in package directory: /root/pkg/", _log);
        return 1; // return an error code
    }

    log("Found. Installing...", _log);

    while (!_host.eof())
    {
        _host.getline(cmd, 2048);
        istringstream _stream(cmd);

        _stream >> _cmd;

        if (_cmd == "#")
            continue;

        else if (_cmd == "name")
        {
            _stream >> _cmd;
            if (_cmd != "=")
                return 1;

            _stream >> _cmd;
            _name = _cmd;

            while(!_stream.eof())
            {
                _stream >> _cmd;
                _name = _name + " " + _cmd;
            }

        }

        else if (_cmd == "id")
        {
            _stream >> _cmd;
            if (_cmd != "=")
                return 1;
            _stream >> _cmd;
            _id = _cmd;
        }

        else if (_cmd == "exec")
        {
            _stream >> _cmd;
            if (_cmd != "=")
                return 1;
            _stream >> _cmd;
            _exec = _cmd;
        }

    }

    _pkglist << _name << endl;
    _pkglist.close();

    return 0;
}

int pkgUninstall (string _pkgname, ofstream* _log)
{
    ifstream _pkglist("/root/user/pkgdata/pkglist", ios_base::in);

    string _input;
    string _dir = "/root/pkg/" + _pkgname;
    char cmd[2048];

    bool _installed = false;

    while (!_pkglist.eof() && !_installed)
    {
        _pkglist.getline(cmd, 2048);
        if (cmd == _pkgname)
            _installed = true;
    }

    if (!_installed)
    {
        log((string)"Command/package \"" + _pkgname + (string)"\" not found.", _log);
        return 1;
    }

    log("Are you sure you would like to uninstall " + _pkgname + "? [Y/N] ", _log);
    prompt(&_input, "");

    if (_input == "N" || _input == "n")
        return 0;

    RemoveDirectoryA(_dir.c_str());

    return 0;
}

int pkgSearch (string _pkgname, ofstream* _log)
{
    ifstream _pkglist("/root/user/pkgdata/pkglist", ios_base::in);

    string _pkgexec;
    string _cmd;
    string _dir = "/root/pkg/" + _pkgname;
    string __dir = "/root/pkg/" + _pkgname + "/host";
    char cmd[2048];

    bool _installed = false;

    while (!_pkglist.eof() && !_installed)
    {
        _pkglist.getline(cmd, 2048);
        if (cmd == _pkgname)
            _installed = true;
    }

    if (!_installed)
    {
        log((string)"Command/package \"" + _pkgname + (string)"\" not found.", _log);
        return 1;
    }

    ifstream _host(__dir.c_str(), ios_base::in);

    if (!_host)
        return 0;

    while(!_host.eof())
    {
        _host.getline(cmd, 2048);
        istringstream _stream(cmd);

        _stream >> _cmd;
        if (_cmd == "exec")
        {
            _stream >> _cmd; // =
            _stream >> _cmd; // filename
            _pkgexec = _cmd;
        }
    }

    _cmd = "exec " + _pkgexec;

    parse(_cmd, _log, &_dir);

    return 0;
}

int pkgInfo (string _pkgname, ofstream* _log)
{
    string _output;
    string _cmd;
    string _dir = "/root/pkg/" + _pkgname + "/host";
    char cmd[2048];

    if (pkgSearch(_pkgname, _log))
        return 0;

    ifstream _host(_dir.c_str(), ios_base::in);

    if (!_host)
        return 0;

    while(!_host.eof())
    {
        _host.getline(cmd, 2048);
        istringstream _stream(cmd);

        _stream >> _cmd;
        if (_cmd == "info")
        {
            _stream >> _cmd; // =
            _stream >> _cmd; // package info
            _output = _cmd;
            while (!_stream.eof())
            {
                _stream >> _cmd;
                _output = _output + " " + _cmd;
            }
        }
    }

    log(_output, _log);

    return 0;
}
