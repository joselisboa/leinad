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

    SetConsoleTitle(TEXT("Leinad"));

    // grelha do mapa
    Grelha grelha(GRELHA_WIDTH, GRELHA_HEIGHT, GRELHA_OFFSET);

    // o jogo
    Leinad leinad(CONSOLA_WIDTH, CONSOLA_HEIGHT, &grelha);

    //TESTE caixas (elementos estáticos)
    Caixas caixas;
    caixas
        .caixa(COORD{ 20, 5 }, 6, 12, '#', leinad.console.BLUE_FADE)
        .caixa(COORD{15, 8}, 16, 3, '#', leinad.console.BLUE_FADE)
        .caixa(COORD{ 26, 11 }, 1, 1, '$', leinad.console.YELLOW)
        .caixa(COORD{6, 31}, 8, 5);
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
