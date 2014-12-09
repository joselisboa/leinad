#ifndef CAIXA_H
#define CAIXA_H

#include <Windows.h>
#include <vector>

using namespace std;

class Caixa
{
    short _width;
    short _height;
    COORD _pos;
    CHAR_INFO _ci;

    //CHAR_INFO *_buffer;
public:
    //CHAR_INFO *buffer() { return _buffer; }

    CHAR_INFO ci() { return _ci; }
    COORD pos() { return _pos; }
    COORD size() { return COORD{_width, _height}; }
    short width() { return _width; }
    short height() { return _height; }

    void width(short width) { _width = width; }
    void height(short height) { _height = height; }

    Caixa(COORD pos, short width, short height, char ch = '#', WORD attr = 8) {
        _width = width;
        _height = height;
        _pos = pos;

        _ci.Char.UnicodeChar = ch;
        _ci.Attributes = attr;

        //_buffer = new CAR_INFO[width*height];
    }
    ~Caixa(){
        //delete[] _buffer;
    }
};

// Caixas
//-------
class Caixas
{
private:
    //TODO ...
    COORD _max;// = { 120, 60 };
    vector<Caixa> _caixas;

public:

    COORD size() { return _max; }

    // adiciona uma caixa
    Caixas &caixa(COORD pos, short width, short height, char ch = '#', WORD attr = 8);

    // devolve caixa na posição pos
    vector<Caixa>::iterator caixa(COORD pos);

    // devolve caixas numa determinada zona
    vector<Caixa> caixas(COORD pos, short width, short height);

    // devolve caixas que contêm um determinado ponto
    vector<Caixa> contem(COORD ponto);

    // construtor
    Caixas(short x = 120, short y = 60) { _max = { x, y }; }
};

#endif
