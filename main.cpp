//
// Leinad
//
// description: School project for OOP (Object Oriented Programming)
// author: Jos� Vieira Lisboa
// url: https://github.com/joselisboa/leinad
//
#include <iomanip>
#include "header.h"

using namespace std;

int main(int argc, char *varc)
{
    SetConsoleTitle(TEXT("Leinad"));

    // configura��o do jogo
    LEINAD CONFIG;//TODO const

    // largura e altura da consola
    CONFIG.consola.dim = DIM2 { 80, 33 };

    // grelha do mapa (zona vis�vel)
    CONFIG.grelha = GRELHA {
        // posi��o na consola
        COORD { 16, 0 },
        // dimens�es
        DIM2 { 64, 32 }
    };

    // ficheiros ...
    CONFIG.mapa = "..\\mapa.txt";
    CONFIG.splash = "..\\leinad.txt";
    //config.rivais = "rivais.txt"

    // criar o jogo
    Leinad leinad(CONFIG);

    // iniciar o jogo
    while (leinad.menu()) {
        leinad.init();
        // mover elemento din�mico
        while (leinad.move()) {
            //TODO mover elementos IA
        }
    }

    return 0;
}
