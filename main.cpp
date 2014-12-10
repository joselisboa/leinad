//
// Leinad
//
// description: School project for OOP (Object Oriented Programming)
// author: José Vieira Lisboa
// url: https://github.com/joselisboa/leinad
//
#include <iomanip>
#include <fstream>
#include "header.h"

using namespace std;

int main(int argc, char *varc)
{
    const COORD GRELHA_OFFSET = { 16, 0 };
    const short GRELHA_WIDTH = 64;
    const short GRELHA_HEIGHT = 32;
    const short CONSOLA_WIDTH = 80;
    const short CONSOLA_HEIGHT = 33;
    string const MAPA{ "c:\\GIT\\leinad\\mapa.txt" };
    //string const RIVAIS{ "rivais.txt" };

    SetConsoleTitle(TEXT("Leinad"));

    // grelha do mapa
    Grelha grelha(GRELHA_WIDTH, GRELHA_HEIGHT, GRELHA_OFFSET);

    // o jogo
    Leinad leinad(CONSOLA_WIDTH, CONSOLA_HEIGHT, &grelha);

    // elementos estáticos
    Caixas caixas;
    ifstream mapa(MAPA);
    if (!mapa) {
        cout << "> ERRO a abrir o ficheiro " << MAPA << endl;
        return 1;
    }
    short x, y, width, height;
    char ch;
    int attr;
    while (mapa >> x) {
        mapa >> y, mapa >> width, mapa >> height, mapa >> ch, mapa >> attr;
        caixas.caixa(COORD{ x, y }, width, height, ch, attr);
    }

    // passar as "caixas" ao jogo
    leinad.caixas(&caixas);

    //TEST iniciar o jogo
    while (leinad.menu()) {
        leinad.init();
        // mover elemento dinâmico
        while (leinad.move()) {
            //TODO mover elementos IA
        }
    }

    return 0;
}
