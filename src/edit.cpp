#include "edit.h"

int edit(fstream* _file, ofstream* _log)
{
    //
    // IDEAS FOR IMPLEMENTATION:
    // char array containing current contents displayed on screen
    // anytime a key is pressed, delete character from array or add
    // and redraw screen
    //
    // ISSUES:
    // - no cursor placement, so fixing error involves writing new file
    // - cannot detect keys for backspacing

    log("Loading file...", _log);

    vector<char> _data;
    vector<char>::iterator _datacurrent;
    int __current;
    char _current;
    string _input;

    COORD _cursor;
    _cursor.X = 0;
    _cursor.Y = 0;

    COORD _oldcursor;
    _oldcursor.X = 0;
    _oldcursor.Y = 0;

    CONSOLE_SCREEN_BUFFER_INFO _screen;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &_screen);

    unsigned int i;

    if (!_file)
    {
        log("File not found.", _log);
        return 0;
    }

    // Read the data from the file
    while (!_file->eof())
    {
        _file->get(_current);
        _data.push_back(_current);
    }

    // Draw the initial screen text
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _HEADER);
    cout << "EDIT MODE | FILE CONTENTS:\n\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _RESET);
    for (i = 0; i < _data.size(); i++)
    {
        cout << _data[i];
    }

    // Unless ESC is pressed, loop through editing
    while ( _current != 0x1B )
    {
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &_screen);
        _cursor.X = _screen.dwCursorPosition.X;
        _cursor.Y = _screen.dwCursorPosition.Y;
        _current = getch();

        if(_current == 8 && _data.size() > 0) // backspace key is pressed
        {
            _data.pop_back();
            system("cls");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _HEADER);
            cout << "EDIT MODE | FILE CONTENTS:\n\n";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _RESET);
            for (i = 0; i < _data.size(); i++)
            {
                cout << _data[i];
            }
        }
        else if (_current == 0x0D)
        {
            _data.insert(_datacurrent, _current);
            cout << endl;
        }
        else if (_current == 0x30)
        {
            _cursor.X -= 1;
            if (_cursor.X < 0)
            {
                _cursor.Y -= 1;
                _cursor.X = 80; // width of console screen, automatically resets to end of line
            }

            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), _cursor);
        }
        else
        {
            _datacurrent = _data.begin();
            __current = 0;
            while (_oldcursor.X != _cursor.X && _oldcursor.Y != _cursor.Y - 2)
            {
                __current += 1;
                if (_data[__current] == '\n')
                {
                    _oldcursor.Y += 1;
                    _oldcursor.X = 0;
                }
                else
                {
                    cout << _data[_current];
                    _oldcursor.X += 1;
                }
            }

            _oldcursor.X = 0;
            _oldcursor.Y = 0;

            _datacurrent += __current;

            _data.insert(_datacurrent, _current);
            system("cls");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _HEADER);
            cout << "EDIT MODE | FILE CONTENTS:\n\n";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _RESET);
            for (i = 0; i < _data.size(); i++)
            {
                cout << _data[i];
            }
            cout << __current;
        }

        _datacurrent = _data.begin();
        _datacurrent += __current;

    }

    system("cls");
    return 0;
}
