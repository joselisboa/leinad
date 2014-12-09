#include <iomanip>
#include <fstream>
#include "header.h"

using namespace std;

int main(int argc, char *varc)
{
    const COORD GRELHA_OFFSET = { 18, 1 };
    const short GRELHA_WIDTH = 60;
    const short GRELHA_HEIGHT = 30;
    const short CONSOLA_WIDTH = 80;
    const short CONSOLA_HEIGHT = 33;

    SetConsoleTitle(TEXT("Leinad"));

    // grelha
    //Grelha grelha(40, 20);// GRELHA.X, GRELHA.Y);
    //grelha.testes();
    //grelha.offset(COORD{ 21, 3 }).fill('?', Ze().RED_FADE).write(Ze().output_handle());
    //grelha.offset(COORD{ 15, 5 }).fill('#', Ze().MAGENTA_FADE).write(Ze().output_handle());

    // Ze
    //cout << "> Ze().textColor(Ze().YELLOW);"<< endl;
    //Ze().textColor(Ze().YELLOW);
    //cout << "> Ze().paintString(\"Jose Daniel\", COORD{ 5, 5 }, Ze().BLUE_FADE | Ze().CYAN_FADE << 4);" << endl;
    //Ze().paintString("Jose Daniel", COORD{ 5, 5 }, Ze().BLUE_FADE | Ze().CYAN_FADE << 4);
    //while (false) {
    //  Ze().input();
    //}

    // grelha do mapa
    Grelha grelha(GRELHA_WIDTH, GRELHA_HEIGHT);
    grelha.offset(GRELHA_OFFSET);

    // o jogo
    Leinad leinad(CONSOLA_WIDTH, CONSOLA_HEIGHT, &grelha);
    leinad.console.hideCursor();

    //TEST um jogador
    Jogador jogador;
    jogador.pos(30, 15).imagem('@', leinad.console.CYAN | leinad.console.BLUE_FADE << 4);

    //TEST caixas (elementos estáticos)
    Caixas caixas;
    caixas
        .caixa(COORD{ 20, 5 }, 6, 12, '#', leinad.console.BLUE_FADE)
        .caixa(COORD{15, 8}, 16, 3, '#', leinad.console.BLUE_FADE)
        .caixa(COORD{ 26, 11 }, 1, 1, '$', leinad.console.YELLOW)
        .caixa(COORD{6, 31}, 8, 5);
    leinad.caixas(&caixas);

    //TEST iniciar o jogo
    leinad.init(jogador);
    while (true) {
        leinad.move(jogador);
    }

    /*
    // write building to console
    leinad.writeBuilding(box1).writeBuilding(box2).writeBuilding(box3);

    // render
    leinad.render();

    // draw player
    leinad.draw(jogador);

    string cmd;
    leinad.console.cursorPosition(COORD{ 8, HEIGHT });

    //getline(cin, cmd);

    //
    leinad.console.showCursor(false).textSize(15, 15).screenSize(WIDTH, HEIGHT).refresh();
    */

    /*
    ifstream dados("c:\\temp\\leinad.map");
    if (!dados) {
        cout << "> ERRO a abrir o ficheiro\n";
        exit(1);
    }
    Ze ze;
    char ch, pc[255];
    int i=0;
    while (dados >> ch && i < 254) {
        ze.cursorPosition(COORD{ i, 10 });
        cout << ch;
        i++;
    }

    pc[i] = (char) '/0';

    for (int x = 0; x < 25; x++)
        for (int y = 0; y < 7; y++) {
            ze.cursorPosition(COORD{ x, y });
            cout << (char) (15 + x + (y * 25));
        }
    */

    //while (false) {
    //
    //  // comando
    //  leinad.move(jogador);

    //  // move rivais
    //}

    return 0;
}
