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
    // dimensão da consola
    COORD _screen;

    // caixas (elementos estáticos)
    Caixas *_caixas;

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

    // consola
    Ze console;

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
    //Leinad &caixas(Caixas *caixas) { _caixas = caixas, _map = _caixas->size(); return *this; }
    Leinad &drawPlayer(Jogador &, bool flag = true);
    Leinad &drawCaixa(Caixa &caixa);
    Leinad &init();
    Leinad &render(Jogador);

    Leinad(LEINAD const);
    ~Leinad();

    Leinad &caixas(string filename);
};

#endif
