//
// Leinad
//
// description: School project for OOP (Object Oriented Programming)
// author: José Vieira Lisboa
// url: https://github.com/joselisboa/leinad
//
#include "grelha.h"

// construtor
Grelha::Grelha(GRELHA config)
{
    dim(config.dim).pos(config.pos);

    _buffer = new CHAR_INFO[_dim.width * _dim.height];

    CHAR_INFO ci;
    ci.Attributes = 8;// Ze().BLUE | Ze().BLUE_FADE << 4;
    ci.Char.UnicodeChar = ' ';
    fill(ci);
}

void Grelha::_makeBox()
{
    _box =  { _pos.X, _pos.Y, _pos.X + (_dim.width - 1), _pos.Y + (_dim.height - 1) };
}

// preenche a grelha com ...
Grelha &Grelha::fill(CHAR_INFO ci)
{
    for (int y = 0; y < _dim.height; y++) {
        for (int x = 0; x < _dim.width; x++) {
            _buffer[x + y * _dim.width] = ci;
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
    return fill(ci);
}

// obtém caractére da posição p
CHAR_INFO Grelha::el(COORD pos)
{
    int i = pos.X + (pos.Y * _dim.width);
    return _buffer[i];
}

// coloca caractére na posição c
Grelha &Grelha::el(COORD pos, CHAR_INFO ci)
{
    int i = pos.X + (pos.Y * _dim.width);
    _buffer[i] = ci;
    return *this;
}
Grelha &Grelha::el(COORD pos, char ch, WORD attr)
{
    CHAR_INFO ci;
    ci.Attributes = attr;
    ci.Char.UnicodeChar = ch;
    this->el(pos, ci);
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
    cout << "> dim().width;// " << dim().width << endl;
    cout << "> dim().height;// " << dim().height << endl;

    // testar offset
    cout << "> pos().X;// " << pos().X << endl;
    cout << "> pos().Y;// " << pos().Y << endl;
    pos(COORD{ 5, 6 });
    cout << "> pos(COORD {5,6});" << endl;
    cout << "> pos().X;// " << pos().X << endl;
    cout << "> pos().Y;// " << pos().Y << endl;

    // testar pos
    cout << "> el(COORD{5,29}).Char.UnicodeChar;// " << el(COORD{ 5, 5 }).Char.UnicodeChar << endl;
    fill('A', 9);
    el(COORD{ 5, 5 }, 'A');
    cout << "> el(COORD{ 5, 19 }, 'A');" << endl;
    cout << "> el(COORD{5,29}).Char.UnicodeChar;// " << el(COORD{ 5, 5 }).Char.UnicodeChar << endl;
    cout << "> (char) el(COORD{5,29}).Char.UnicodeChar;// " << (char) el(COORD{ 5, 5 }).Char.UnicodeChar << endl;

    WriteConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), _buffer, size(), _pos, &_box);
}
