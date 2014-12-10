//
// Leinad
//
// description: School project for OOP (Object Oriented Programming)
// author: José Vieira Lisboa
// url: https://github.com/joselisboa/leinad
//
#include "grelha.h"

// construtor
Grelha::Grelha(short width, short height, COORD offset)
{
    _width = width, _height = height;
    _buffer = new CHAR_INFO[_width * _height];
    //_offset.X = 0, _offset.Y = 0;
    _offset = offset;

    _make_box();
    //_box = { _offset.X, _offset.Y, _offset.X + (_width - 1), _offset.Y + (_height - 1) };

    CHAR_INFO ci;
    ci.Attributes = 8;// Ze().BLUE | Ze().BLUE_FADE << 4;
    ci.Char.UnicodeChar = ' ';
    fill(ci);
}

void Grelha::_make_box()
{
    _box =  { _offset.X, _offset.Y, _offset.X + (_width - 1), _offset.Y + (_height - 1) };
}

// preenche a grelha com ...
Grelha &Grelha::fill(CHAR_INFO ci)
{
    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {
            _buffer[x + y * _width] = ci;
        }
    }
    return *this;
}
// preenche a grelha com ...
Grelha &Grelha::fill(char ch, WORD attr)
{
    CHAR_INFO ci;
    ci.Attributes = attr;
    ci.Char.UnicodeChar = ch;
    fill(ci);
    return *this;
}

// obtém caractére da posição p
CHAR_INFO Grelha::pos(COORD pos)
{
    int i = pos.X + (pos.Y * _width);
    return _buffer[i];
}

// coloca caractére na posição c
Grelha &Grelha::pos(COORD pos, CHAR_INFO ci)
{
    int i = pos.X + (pos.Y * _width);
    _buffer[i] = ci;
    return *this;
}
Grelha &Grelha::pos(COORD pos, char ch, WORD attr)
{
    CHAR_INFO ci;
    ci.Attributes = attr;
    ci.Char.UnicodeChar = ch;
    this->pos(pos, ci);
    return *this;
}

void Grelha::testes()
{
    // testar dimensões
    cout << "> grelha" << endl;
    cout << "> width();// " << width() << endl;
    cout << "> height();// " << height() << endl;
    cout << "> size().X;// " << size().X << endl;
    cout << "> size().Y;// " << size().Y << endl;

    // testar offset
    cout << "> offset().X;// " << offset().X << endl;
    cout << "> offset().Y;// " << offset().Y << endl;
    offset(COORD{ 5, 6 });
    cout << "> offset(COORD {5,6});" << endl;
    cout << "> offset().X;// " << offset().X << endl;
    cout << "> offset().Y;// " << offset().Y << endl;

    // testar pos
    cout << "> pos(COORD{5,29}).Char.UnicodeChar;// " << pos(COORD{ 5, 5 }).Char.UnicodeChar << endl;
    fill('A', 9);
    pos(COORD{ 5, 5 }, 'A');
    cout << "> pos(COORD{ 5, 19 }, 'A');" << endl;
    cout << "> pos(COORD{5,29}).Char.UnicodeChar;// " << pos(COORD{ 5, 5 }).Char.UnicodeChar << endl;
    cout << "> (char) pos(COORD{5,29}).Char.UnicodeChar;// " << (char)pos(COORD{ 5, 5 }).Char.UnicodeChar << endl;

    WriteConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), _buffer, size(), _offset, &_box);
}
