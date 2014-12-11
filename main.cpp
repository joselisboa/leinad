//
// Leinad
//
// description: School project for OOP (Object Oriented Programming)
// author: José Vieira Lisboa
// url: https://github.com/joselisboa/leinad
//
#include <iomanip>
#include "header.h"

using namespace std;

int main(int argc, char *varc)
{
    SetConsoleTitle(TEXT("Leinad"));

    // configuração do jogo
    LEINAD config;

    // largura e altura da consola
    config.consola.dim = DIM2 { 80, 33 };

    // grelha (da zona visível) do mapa
    config.grelha = GRELHA {
        { 16, 0 },// posição (na consola)
        { 64, 32 }// dimensões
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
        // mover elemento dinâmico
        while (leinad.move()) {
            //TODO mover elementos IA
        }
    }

    return 0;
}
