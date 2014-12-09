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
    Caixas *_caixas = nullptr;
    COORD _M;
    COORD _map;
    COORD _screen;
    Grelha *_grelha;
    void _draw(CHAR_INFO, COORD);
    void _info(COORD c);
    bool _colision(COORD pos, char = '#');

public:
    Leinad &drawPlayer(Jogador &, bool flag = true);
    Leinad &move(Jogador &);
    Leinad &right(Jogador &);
    Leinad &left(Jogador &);
    Leinad &up(Jogador &);
    Leinad &down(Jogador &);
    Leinad &M(COORD M) { _M = M; return *this; }
    COORD M() { return _M; }
    void caixas(Caixas *caixas) { _caixas = caixas; }

    Leinad(short, short, Grelha *);
    ~Leinad();

    //TODO mover para privado?
    Ze console;

    void info(string);

    Leinad &drawCaixa(Caixa &caixa)
    {
        for (int x = caixa.pos().X; x < caixa.pos().X + caixa.width(); x++) {
            for (int y = caixa.pos().Y; y < caixa.pos().Y + caixa.height(); y++) {
                //TODO ponto pertence à grelha do mapa?

                _grelha->pos(COORD{ x -_M.X , y - _M.Y }, caixa.ci());
            }
        }
        return *this;
    }

    Leinad &init(Jogador jogador) { return render(jogador); }
    Leinad &render(Jogador jogador)
    {
        // setup grelha
        (*_grelha).fill('.', console.BLUE | console.BLUE_FADE << 4);

        // desenhar as caixas
        if (_caixas != nullptr)
            for (Caixa caixa : _caixas->caixas(_M, 60, 30)) {
                drawCaixa(caixa);
        }

        // escrever na consola
        (*_grelha).write(console.output_handle());

        //TEMP mostrar o jogador
        drawPlayer(jogador);

        ////TODO desenhar outros jogadores
        //drawPlayer(jogador);// desenhar jogador

        return *this;
    }
};

#endif
