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
    char _current;
    string _input;

    COORD _cursor;
    _cursor.X = 0;
    _cursor.Y = 0;

    CONSOLE_SCREEN_BUFFER_INFO _screen;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &_screen);

    unsigned int i;

    // Read the data from the file
    while (!_file->eof())
    {
        _file->get(_current);
        _data.push_back(_current);
    }

    // Draw the initial screen text
    system("cls");
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
            for (i = 0; i < _data.size(); i++)
            {
                cout << _data[i];
            }
        }
        else if (_current == 0x0D)
        {
            _data.push_back(_current);
            cout << endl;
        }
        else if (_current == 0x25)
        {
            _cursor.X -= 1;
            if (_cursor.X < 0)
            {
                _cursor.Y -= 1;
                _cursor.X = 25; // width of console screen, automatically resets to end of line
            }

            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), _cursor);
        }
        else
        {
            _data.push_back(_current);
            cout << _current;
        }

    }

    system("cls");
    return 0;
}
