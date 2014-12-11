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
#include "ze.h"
#include "jogador.h"
#include "grelha.h"
#include "caixa.h"

using namespace std;

typedef struct _dim {
    union dimension
    {
        int width;
        int height;
    };
} DIM;

typedef struct _dim2 {
    int width;
    int height;
} DIM2;

typedef struct _dim3 {
    int width;
    int height;
    int depth;
} DIM3;

typedef struct _moldura {
    COORD pos;
    DIM2 dim;
} GRELHA, FRAME;

typedef struct _leinad {
    FRAME consola;
    FRAME grelha;
    FRAME painel;
    string mapa;
    string splash;
    string jogadores;
} LEINAD;

// Leinad
//-------
class Leinad
{
private:
    COORD _screen;// dimensão da consola
    Caixas *_caixas;// elementos estáticos
    COORD _map;// dimensão do mapa
    COORD _M;// offset da grelha no mapa
    Grelha *_grelha;// grelha do mapa
    Grelha *_painel;// painel de pontuação
    Grelha *_barra;// barra de informação
    Ze console;// consola

    // funções ajudantes
    void _draw(CHAR_INFO, COORD);
    void _info(COORD c);
    bool _colision(COORD pos, char = '#');

    //TEMP dummies
    Jogador dummy;
    void _dummy_panel();

public:
    BOOL menu();
    BOOL move();
    COORD M() { return _M; }
    Leinad &right(Jogador &);
    Leinad &left(Jogador &);
    Leinad &up(Jogador &);
    Leinad &down(Jogador &);
    Leinad &M(COORD M) { _M = M; return *this; }
    Leinad &caixas(string filename);
    Leinad &drawPlayer(Jogador &, bool flag = true);
    Leinad &drawCaixa(Caixa &caixa);
    Leinad &init();
    Leinad &render(Jogador);

    Leinad(LEINAD const);
    ~Leinad() { delete _barra, _painel, _grelha; }
};

#endif
