//
// Leinad
//
// description: School project for OOP (Object Oriented Programming)
// author: José Vieira Lisboa
// url: https://github.com/joselisboa/leinad
//
#ifndef LEINAD_H
#define LEINAD_H
#include <vector>
#include "c:\\htdocs\\ze\\ze.h"
#include "jogador.h"
#include "grelha.h"
#include "caixa.h"

using namespace std;

// Leinad
//-------
class Leinad
{
private:
    // dimensão da consola
    COORD _screen;

    // caixas (elementos estáticos)
    Caixas *_caixas = nullptr;

    // dimensão do mapa
    COORD _map;

    // offset da grelha no mapa
    COORD _M;

    // grelha do mapa
    Grelha *_grelha;

    // painel de pontuação
    Grelha *_painel;

    // barra de informação
    Grelha *_barra;

    // funções ajudantes
    void _draw(CHAR_INFO, COORD);
    void _info(COORD c);
    void info(string);
    bool _colision(COORD pos, char = '#');

    //TESTE
    Jogador dummie;

public:
    BOOL menu();
    BOOL move();
    COORD M() { return _M; }
    Leinad &right(Jogador &);
    Leinad &left(Jogador &);
    Leinad &up(Jogador &);
    Leinad &down(Jogador &);
    Leinad &M(COORD M) { _M = M; return *this; }
    Leinad &caixas(Caixas *caixas) { _caixas = caixas, _map = _caixas->size(); return *this; }
    Leinad &drawPlayer(Jogador &, bool flag = true);
    Leinad &drawCaixa(Caixa &caixa);
    Leinad &init();
    Leinad &render(Jogador);

    Leinad(short, short, Grelha *);
    ~Leinad();

    //TODO mover para privado?
    Ze console;

};

#endif
