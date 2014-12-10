//
// Leinad
//
// description: School project for OOP (Object Oriented Programming)
// author: José Vieira Lisboa
// url: https://github.com/joselisboa/leinad
//
#include "jogador.h"

Jogador::Jogador(int x, int y, char ch, WORD attr)
{
    pos(x, y);
    imagem(ch, attr);
}
