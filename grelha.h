//
// Leinad
//
// description: School project for OOP (Object Oriented Programming)
// author: José Vieira Lisboa
// url: https://github.com/joselisboa/leinad
//
#ifndef GRELHA_H
#define GRELHA_H
#include <Windows.h>
#include "ze.h"
#include <iostream>

using namespace std;

typedef struct _moldura {
    COORD pos;
    DIM2 dim;
} GRELHA, FRAME;

class Grelha
{
    DIM2 _dim;// dimensões da grelha
    COORD _pos;// posição da grelha
    CHAR_INFO *_buffer = nullptr;//ATENÇÃO *_buffer (buffer da grelha) depende de _dim
    SMALL_RECT _box;// caixa do buffer da grelha
    void _makeBox();

public:
    short width() const { return _dim.width; }
    short height() const { return _dim.height; }
    Grelha &width(short width) { _dim.width = width; _makeBox(); return *this; }
    Grelha &height(short height) { _dim.height = height; _makeBox(); return *this; }
    Grelha &dim(DIM2 size) { _dim = size; _makeBox();  return *this; }
    DIM2 dim() { return _dim; }
    COORD size() { return COORD{ _dim.width, _dim.height}; }
    FRAME frame() { return FRAME { _pos, _dim }; }
    COORD pos() { return _pos; }// posição da grelha
    Grelha &pos(COORD pos) { _pos = pos; _makeBox(); return *this; }
    CHAR_INFO el(COORD);// elementos da grelha
    Grelha &el(COORD, CHAR_INFO);
    Grelha &el(COORD pos, char ch, WORD attr = 8);
    Grelha &fill(CHAR_INFO);
    Grelha &fill(char, WORD);

    // escreve o conteúdo da grelha no ecrã
    Grelha &write(HANDLE handle) { WriteConsoleOutput(handle, _buffer, size(), COORD { 0, 0 }, &_box); return *this; }

    Grelha(GRELHA config);
    ~Grelha() { delete [] _buffer; }

    //TODO remover estas funções (ver Leinad render())
    SMALL_RECT *box() { return &_box; }
    CHAR_INFO *buffer() const { return _buffer; }

    // testes...
    void testes();
};

#endif
