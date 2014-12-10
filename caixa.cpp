#include "caixa.h"

COORD const MAX = { 120, 60 };// ?
BOOL OR(BOOL A, BOOL B) { return (A || B); }
BOOL NOR(BOOL A, BOOL B) { return (!A && !B); }// return !OR(A, B); }//
BOOL AND(BOOL A, BOOL B) { return (A && B); }
BOOL NAND(BOOL A, BOOL B) { return (!A || !B); }//return !AND(A, B); };//

// Caixas
//-------

Caixas &Caixas::caixa(COORD pos, short width, short height, char ch, WORD attr)
{
    // validar a caixa
    if (NOR(pos.X < 0, pos.Y < 0) && // não tem coordenadas negativas
        NOR(pos.X > _max.X, pos.Y > _max.Y)) { // não tem coordenadas maiores que _max
        _caixas.push_back(Caixa(pos, width, height, ch, attr));
    }

    return *this;
}

// devolve (iterador da) caixa na posição pos (do mapa)
vector<Caixa>::iterator Caixas::caixa(COORD pos)
{
    vector<Caixa>::iterator it = _caixas.begin();
    for (it; it != _caixas.end(); it++) {
        if (pos.X == it->pos().X && pos.Y == it->pos().Y) {
            return it;
        }
    }

    return it;
}

// devolve caixas definidas numa determinada zona
vector<Caixa> Caixas::caixas(COORD pos, short width, short height)
{
    vector<Caixa> caixas;

    for (Caixa caixa : _caixas) {
        // cantos da caixa
        COORD P[4];
        P[0] = caixa.pos();
        P[1] = { P[0].X, P[0].Y + caixa.height() - 1 };
        P[2] = { P[0].X + caixa.width() - 1, P[0].Y };
        P[3] = { P[0].X + caixa.width() - 1, P[0].Y + caixa.height() - 1 };
        for (int i = 0; i < 4; i++) {
            // dentro da zona
            if (NOR(P[i].X - pos.X < 0, P[i].X - pos.X > width + 1) &&
                NOR(P[i].Y - pos.Y < 0, P[i].Y - pos.Y > height + 1)) {
                caixas.push_back(caixa);
                break;
            }
        }
    }

    return caixas;
}

// devolve ás caixas que comtêm um determinado ponto
vector<Caixa> Caixas::contem(COORD ponto)
{
    vector<Caixa> caixas;

    for (Caixa caixa : _caixas) {
        // coordenada da caixa
        COORD P = caixa.pos();
        COORD size = caixa.size();
        // dentro da caixa
        if (NOR(ponto.X - P.X < 0, ponto.X - P.X > size.X) &&
            NOR(ponto.Y - P.Y < 0, ponto.Y - P.Y > size.Y)) {
            caixas.push_back(caixa);
        }
    }

    return caixas;
}
