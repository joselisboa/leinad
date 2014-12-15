//
// Leinad
//
// description: School project for OOP (Object Oriented Programming)
// author: Jos� Vieira Lisboa
// url: https://github.com/joselisboa/leinad
//
#include "header.h"

using namespace std;

int main(int argc, char *varc)
{
    SetConsoleTitle(TEXT("Leinad"));

    // configura��o do jogo
    LEINAD config;

    // dimens�es da consola (largura, altura)
    config.consola.dim = { 80, 33 };

    // posi��o na consola (x, y) e dimens�es (largura, altura) da grelha do mapa
    config.grelha = {{ 16, 0 }, { 64, 32 }};

    // ficheiros ...
    config.mapa = "..\\mapa.txt";
    config.splash = "..\\leinad.txt";
    //config.rivais = "rivais.txt"

    // criar o jogo
    Leinad leinad(config);

    // iniciar o jogo
    while (leinad.menu()) {
        leinad.init();

        // mover elemento din�mico
        while (leinad.move()) {
            //TODO AI (Artificial Inteligence)
        }
    }

    return 0;
}
