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

    // buffer e caixa da grelha
    CHAR_INFO *_buffer = nullptr;
    SMALL_RECT _box;
    void _makeBox();

public:
    // dimensões da grelha
    short width() const { return _dim.width; }
    short height() const { return _dim.height; }
    
    COORD size() { return COORD{ _dim.width, _dim.height}; }
    
    Grelha &width(short width) { _dim.width = width; _makeBox(); return *this; }
    Grelha &height(short height) { _dim.height = height; _makeBox(); return *this; }
    Grelha &dim(DIM2 size) { _dim = size; _makeBox();  return *this; }
    DIM2 dim() { return _dim; }
    FRAME frame() { return FRAME { _pos, _dim }; }
    
    // can't change size becauso of *_buffer
    //Grelha &size(short width, short height);

    // posição da grelha
    COORD pos2() { return _pos; }
    Grelha &pos2(COORD pos) { _pos = pos; _makeBox(); return *this; }
    
    //TODO delete
    COORD offset() { return pos2(); }
    Grelha &offset(COORD offset) {return pos2(offset); }

    // elementos da grelha
    CHAR_INFO pos(COORD);
    Grelha &pos(COORD, CHAR_INFO);
    Grelha &pos(COORD pos, char ch, WORD attr = 8);
    Grelha &fill(CHAR_INFO);
    Grelha &fill(char, WORD);

    // escrever o conteúdo da grelha no ecrã
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
