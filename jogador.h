//
// Leinad
//
// description: School project for OOP (Object Oriented Programming)
// author: José Vieira Lisboa
// url: https://github.com/joselisboa/leinad
//
#ifndef JOGADOR_H
#define JOGADOR_H

#include "ze.h"

using namespace std;

class Jogador
{
    CHAR_INFO _imagem;
    COORD _pos;
    //COORD _last_pos;

public:

    COORD pos() const { return _pos; }
    Jogador &pos(short x, short y) { _pos.X = x, _pos.Y = y; return *this; }
    Jogador &imagem(char ch, WORD attr) { _imagem.Char.UnicodeChar = ch; _imagem.Attributes = attr; return *this; }
    CHAR_INFO imagem() const { return _imagem; }

    Jogador(int x = 0, int y = 0, char ch = '@', WORD attr = Ze().MAGENTA);
};

#endif
