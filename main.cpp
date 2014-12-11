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
    LEINAD config;

    // largura e altura da consola
    config.consola.dim = DIM2 { 80, 33 };

    // grelha (da zona vis�vel) do mapa
    config.grelha = GRELHA {
        { 16, 0 },// posi��o (na consola)
        { 64, 32 }// dimens�es
    };

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
            //TODO mover elementos IA
        }
    }

    return 0;
}
