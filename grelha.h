#ifndef GRELHA_H
#define GRELHA_H
#include <Windows.h>
#include <iostream>

using namespace std;

class Grelha
{
    // largura e altura da grelha
    short _width;
    short _height;

    // buffer e caixa da grelha
    CHAR_INFO *_buffer;
    SMALL_RECT _box;
    void _make_box();

    // offset dagrelha
    COORD _offset;

public:
    // dimensões da grelha
    short width() const { return _width; }
    short height() const { return _height; }
    COORD size() { return COORD{_width, _height}; }
    Grelha &width(short width) { _width = width; _make_box(); return *this; }
    Grelha &height(short height) { _height = height; _make_box(); return *this; }

    // can't change size becauso of *_buffer
    //Grelha &size(short width, short height);

    // posição da grelha
    COORD offset() { return _offset; }
    Grelha &offset(COORD offset) { _offset = offset; _make_box(); return *this; }

    // elementos da grelha
    CHAR_INFO pos(COORD);
    Grelha &pos(COORD, CHAR_INFO);
    Grelha &pos(COORD pos, char ch, WORD attr = 8);
    Grelha &fill(CHAR_INFO);
    Grelha &fill(char, WORD);

    // escrever o conteúdo da grelha no ecrã
    Grelha &write(HANDLE handle) { WriteConsoleOutput(handle, _buffer, size(), COORD { 0, 0 }, &_box); return *this; }

    Grelha(short width, short height);
    ~Grelha() { delete [] _buffer; }

    //TODO remover estas funções (ver Leinad render())
    SMALL_RECT *box() { return &_box; }
    CHAR_INFO *buffer() const { return _buffer; }

    // testes...
    void testes();
};

#endif
