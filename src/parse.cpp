#include "parse.h"

using namespace std;

int parse(string cmd, ofstream* _log, string* _currentdir)
{
    istringstream _stream(cmd);
    string _cmd;

    _stream >> _cmd;

    if(_cmd == "sd") // ShutDown
        return 0;

    else if(_cmd == "help") // Help
    {
        _stream >> _cmd;

        if (_stream.eof() && _cmd == "help")
            log("usage: help [topic]\n\nHelp Topics:\ncommands\tpackages\n", _log);

        else if (_cmd == "commands")
            log("Commmands are used in ROOT by simply typing in the name of the command you would like to execute when the prompt appears and pressing the ENTER key. The topics displayed in the help menu correspond to commands that you can execute in the console. To see help for a specific command, use \"[command] info\" or \"[command] help\".", _log);

        else if (_cmd == "packages")
            log("Packages are applications that can add features and commands to extend the functionality of the ROOT environment. You can install packages by executing the following command:\n\npkg install [package-name]\n\nTo view more help on the \"pkg\" command, use \"pkg info\" or \"pkg help\".", _log);

        else
            log((string)"Help topic \"" + _cmd + (string)"\" not found.", _log);

    }

    else if(_cmd == "pkg") // Package
    {
        _stream >> _cmd;

        if ((_stream.eof() && _cmd == "pkg") || _cmd == "help" || _cmd == "info")
            log("usage: pkg [install; update; uninstall; info] [name; id]", _log);

        else if (_cmd == "install")
        {
            _stream >> _cmd;

            if (_stream.eof() && _cmd == "install")
                log("usage: package install [name; id]", _log);

            else
                pkgInstall(_cmd, _log);
        }

        else
            log("usage: pkg [install; update; uninstall; info] [name; id]", _log);

    }

    else if (_cmd == "clear")
    {
        _stream >> _cmd;

        if (_cmd == "help" || _cmd == "info")
            log("usage: clear\nClears the current text on the window.", _log);

        else
            system("cls");

    }

    else if (_cmd == "read")
    {
        _stream >> _cmd;

        if ((_stream.eof() && _cmd == "read") || _cmd == "help" || _cmd == "info")
            log("usage: read [filename]\nPrint the contents of a file.", _log);

        else
        {
            string _dir = *_currentdir + "/" + _cmd;

            ifstream _readfile(_dir.c_str(), ios_base::in);
            string _contents;
            char _current;

            if (!_readfile)
                log((string)"Unknown file: " + _cmd, _log);

            else
            {
                log(_cmd + (string)":\n", _log);
                while (!_readfile.eof())
                {
                    // append read character to output string
                    _readfile.get(_current);
                    _contents = _contents + _current;
                }
                log(_contents, _log);
            } // !readfile

        } // _stream.eof

    } // read

    else if (_cmd == "cd")
    {
        string _dir;
        _stream >> _cmd;

        if ((_stream.eof() && _cmd == "cd") || _cmd == "help" || _cmd == "info")
            log("usage: cd [directory]\nChange the current working directory.", _log);

        else
        {
            _dir = _cmd;
            while (!_stream.eof())
            {
                _dir = _dir + _cmd;
            }

            *_currentdir = _dir;
        }
    }

    else if (_cmd == "dirs")
    {

    }

    else if (_cmd == "edit")
    {
        string _filename;
        _stream >> _cmd;

        if ((_stream.eof() && _cmd == "edit") || _cmd == "help" || _cmd == "info")
            log("usage: edit [filename]\nEdit the contents of a file.", _log);

        else
        {
            _filename = *_currentdir + "/" + _cmd;
            fstream _edit(_filename.c_str());
            edit(&_edit, _log);
        }
    }

    else if (_cmd == "exec")
    {
        _stream >> _cmd;

        if ((_stream.eof() && _cmd == "exec") || _cmd == "help" || _cmd == "info")
            log("usage: exec [file]\nExecute the specified file; file must be of type \".re\"", _log);

        else
            exec(_cmd, _log, _currentdir);
    }

    else if (_cmd == "")
        return 1;

    else // default
        pkgSearch(_cmd, _log);

    return 0;
}
