#include "exec.h"

int exec(string _filename, ofstream* _log, string* _currentdir)
{
    // Variable array
    map<string, string> _vars;
    string _dir = *_currentdir + "/" + _filename;

    ifstream _exec(_dir.c_str(), ios_base::in);
    char cmd[2048];
    string _cmd;

    if (!_exec)
        return 0;

    while (!_exec.eof())
    {
        _exec.getline(cmd, 2048);
        istringstream _stream(cmd);

        execparse(&_stream, &_exec, &_vars, _log, _currentdir);
    }

    return 0;
}

int execparse(istringstream* _stream, ifstream* _exec, map<string, string>* _vars, ofstream* _log, string* _currentdir)
{
    char cmd[2048];
    string _cmd;
    *_stream >> _cmd;

    if (_cmd == "var")
    {
        string __cmd;
        string _value = "";
        *_stream >> _cmd;

        if ((_stream->eof() && _cmd == "var") || _cmd == "help" || _cmd == "info")
            log("usage: var [name] [value]\nRegister a new variable for use in executables.", _log);

        else
        {
            *_stream >> __cmd;
            if (__cmd != "=")
            {
                log((string)"error: assignment operator expected after \"" + _cmd + (string)"\"", _log);
                return 0;
            }

            *_stream >> __cmd;
            _value = __cmd;
            if (_value == "=")
            {
                log("error: expected value after assignment", _log);
                return 0;
            }
            while(!_stream->eof())
            {
                *_stream >> __cmd;
                if (__cmd == "%%")
                {
                    *_stream >> __cmd;
                    map<string, string>::iterator __value;
                    __value = _vars->find(__cmd);

                    if (__value != _vars->end())
                    {
                        _value = _value + " " + __value->second;
                        continue;
                    }
                    else
                        log((string)"error: variable \"" + _cmd + (string)"\" not found.", _log);
                }


                _value = _value + " " + __cmd;
            }

            _vars->insert(pair<string, string>(_cmd, _value));
        }
    }

    else if (_cmd == "input")
    {
        string _input;
        *_stream >> _cmd;

        if ((_stream->eof() && _cmd == "input") || _cmd == "help" || _cmd == "info")
            log("usage: input [var]\nPrompt the user for input and to be logged into variable [var].", _log);

        else
        {
            prompt(&_input, "");
            map<string, string>::iterator _var;
            _var = _vars->find(_cmd);
            if (_var != _vars->end())
                _var->second = _input;
            else
                log("error: variable " + _cmd + " not found", _log);

        }

    }

    else if (_cmd == "echo")
    {
        string _input;
        *_stream >> _cmd;

        if ((_stream->eof() && _cmd == "echo") || _cmd == "help" || _cmd == "info")
            log("usage: echo [var]\nLog the contents of a variable.", _log);

        else
        {
            map<string, string>::iterator _value;
            _value = _vars->find(_cmd);

            if (_value != _vars->end())
                log(_value->second, _log);
            else
                log((string)"error: variable \"" + _cmd + (string)"\" not found.", _log);
        }
    }
    else if (_cmd == "log")
    {
        string _output = "";
        *_stream >> _cmd;

        if ((_stream->eof() && _cmd == "log") || _cmd == "help" || _cmd == "info")
            log("usage: log [text]\nLog the provided text to the ROOT log file.", _log);

        else
        {
            _output = _cmd;
            while (!_stream->eof())
            {
                *_stream >> _cmd;
                _output = _output + " " + _cmd;
            }
            logf(_output, _log);
        }
    }
    else if (_cmd == "say")
    {
        string _output = "";
        *_stream >> _cmd;

        if ((_stream->eof() && _cmd == "say") || _cmd == "help" || _cmd == "info")
            log("usage: say [text]\nEcho the provided text to the console.", _log);

        else
        {
            _output = _cmd;

            // Check for variable before entering loop, so as not to skip it
            if (_cmd == "%%")
            {
                *_stream >> _cmd;
                map<string, string>::iterator _value;
                _value = _vars->find(_cmd);

                if (_value != _vars->end())
                {
                    _output = _value->second;
                }
                else
                    log((string)"error: variable \"" + _cmd + (string)"\" not found.", _log);
            }

            while (!_stream->eof())
            {
                *_stream >> _cmd;

                if (_cmd == "%%")
                {
                    *_stream >> _cmd;
                    map<string, string>::iterator _value;
                    _value = _vars->find(_cmd);

                    if (_value != _vars->end())
                    {
                        _output = _output + " " + _value->second;
                        continue;
                    }
                    else
                        log((string)"error: variable \"" + _cmd + (string)"\" not found.", _log);
                }
                _output = _output + " " + _cmd;
            }
            log(_output, _log);
        }
    }

    else if (_cmd == "if")
    {
        string _value1;
        string _value2;
        string _operator;
        *_stream >> _cmd;

        if ((_stream->eof() && _cmd == "say") || _cmd == "help" || _cmd == "info")
            log("usage: if [value] [logical operator] [value]\nRun a conditional \"if\" statement, where if the provided statement is true, the embedded code will run.", _log);

        else
        {
            if (_cmd == "%%")
            {
                *_stream >> _cmd;
                map<string, string>::iterator _value;
                _value = _vars->find(_cmd);

                if (_value != _vars->end())
                {
                    _value1 = _value->second;
                }
                else
                    log((string)"error: variable \"" + _cmd + (string)"\" not found.", _log);
            }
            else
            {
                while(_cmd != ".and." && _cmd != ".or." && _cmd != ".equals.")
                {
                    _value1 += _cmd;
                    *_stream >> _cmd;
                }
                _operator = _cmd;
            }

            *_stream >> _cmd;
            _operator = _cmd;

            do
            {
                *_stream >> _cmd;
                _value2 += _cmd;
            } while (!_stream->eof());

            if (_operator == ".equals.")
            {
                if (_value1 == _value2)
                {
                    // Code here... possible provide pointer to actual ifstream? for getline, then process istringstream here
                    _exec->getline(cmd, 2048);
                    istringstream __stream(cmd);
                    bool _exit;
                    while(!_exit)
                    {
                        _exit = execparse(&__stream, _exec, _vars, _log, _currentdir);
                    }
                }
            }


//            else if (_operator == ".or.")
//            {
//                if (_value1 || _value2)
//                    return 1;
//            }
//
//            else if (_operator == ".and.")
//                if (_value1 && _value2)
//                    return 1;
//            }

        }

    }

    else if (_cmd == "end")
        return 1;

    else if (_cmd == "#")
        return 0;

    else if (_exec->eof())
        return 1;

    else
        return parse(_cmd, _log, _currentdir);

    return 0;
}
