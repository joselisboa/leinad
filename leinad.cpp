//
// Leinad
//
// description: School project for OOP (Object Oriented Programming)
// author: José Vieira Lisboa
// url: https://github.com/joselisboa/leinad
//
#include <iostream>
#include "leinad.h"

using namespace std;

string const NOME{ "LEINAD" };
string desc = "Trabalho Pratico POO | ISEC 2014 | 21230536, Jose Vieira Lisboa";

BOOL Leinad::menu()
{
    console.cls(console.MAGENTA_FADE);

    int x = (_screen.X - NOME.length()) / 2,  y = _screen.Y / 2;
    console.cursorPosition(COORD{ x, y }).textColor(15 | console.MAGENTA_FADE << 4);
    cout << NOME;

    x = (_screen.X - desc.length()) / 2, y = _screen.Y - 2;
    console.cursorPosition(COORD{ x, y }).textColor(13 | console.MAGENTA_FADE << 4);
    cout << desc;

    // esperar que se carregue uma tecla
    while (!console.ch());

    // descrição na consola
    console.cls(console.MAGENTA_FADE);
    x = (_screen.X - desc.length()) / 2, y = _screen.Y - 2;
    console.cursorPosition(COORD{ x, y }).textColor(13 | console.MAGENTA_FADE << 4);
    cout << desc;

    // opções inicias do menu (desactivado)
    bool play = true, enabled = false;
    COORD O = { (_screen.X - 6) / 2, _screen.Y / 4 };
    _menu(O, 1 | console.MAGENTA_FADE << 4, " PLAY ");
    _menu(COORD{ O.X, O.Y + 4 }, 1 | console.MAGENTA_FADE << 4, " EXIT ");

    //TODO delegar esta tarefa a uma função
    while (true) {
        switch (console.ch()) {
            case VK_UP:
            case VK_DOWN:
                if (!enabled) {
                    enabled = true;
                    _menu(O, 1 | console.MAGENTA << 4, " PLAY ");
                    break;
                }
                if (play) {
                    play = !play;
                    _menu(O, 1 | console.MAGENTA_FADE << 4, " PLAY ");
                    _menu(COORD{ O.X,  O.Y + 4}, 1 | console.MAGENTA << 4, " EXIT ");
                }
                else {
                    play = !play;
                    _menu(O, 1 | console.MAGENTA << 4, " PLAY ");
                    _menu(COORD{ O.X, O.Y + 4 }, 1 | console.MAGENTA_FADE << 4, " EXIT ");
                }
                break;

            // ENTER KEY
            case 13:
                if (enabled) {
                    if (play) return true;
                    else {
                        console.cls(console.BLACK);
                        console.foreground(8);
                        return false;
                    }
                }
                break;
            default:;
        }
    }

    // sair normalmente
    return true;
}

BOOL Leinad::move()
{
    // ler input da consola
    ReadConsoleInput(console.input(), &console.input_record, 1, &console.info);

    // evento do teclado
    if (console.input_record.EventType == KEY_EVENT && console.input_record.Event.KeyEvent.bKeyDown) {
        // apaga o jogador
        drawPlayer(dummie, false);

        // nova posição do Jogador
        switch (console.input_record.Event.KeyEvent.wVirtualKeyCode) {
        case VK_RIGHT:
            right(dummie);
            break;
        case VK_LEFT:
            left(dummie);
            break;
        case VK_UP:
            up(dummie);
            break;
        case VK_DOWN:
            down(dummie);
            break;
        case 27: return false;
        default:;

        }
        // desenha o jogador
        drawPlayer(dummie, true);

        console.cursorPosition(_screen.X - 16, _screen.Y-1);
        console.textColor(console.GREEN | console.GREEN_FADE << 4);
        cout << "TECLA(" << console.input_record.Event.KeyEvent.wVirtualKeyCode << ")  ";
    }

    // limpar o buffer de input da consola
    FlushConsoleInputBuffer(console.input());

    // saída normal ...
    return true;
}

Leinad &Leinad::right(Jogador &jogador)
{
    COORD pos = jogador.pos();
    pos.X++;

    if (_colision(pos)) return *this;


    // existe mapa não visível e penúltima linha da grelha
    if (pos.X + _M.X < _map.X - 1 && pos.X > _grelha->width() - 2) {
        // manter na penúltima linha ...
        pos.X = _grelha->width() - 2;
        // deslocar o mapa
        if (pos.X < _M.X + _map.X) {
            _M.X++;
            // desenhar jogador
            render(jogador);
            //TODO desenhar outros jogadores
        }
    }

    // última linha da grelha
    else if (pos.X > _grelha->width() - 1) pos.X = _grelha->width() - 1;

    jogador.pos(pos.X, pos.Y);

    return *this;
}

Leinad &Leinad::left(Jogador &jogador)
{
    COORD pos = jogador.pos();
    pos.X--;

    if (_colision(pos)) return *this;

    // existe mapa não visível e segunda linha da grelha
    if (_M.X > 0 && pos.X == 0) {
        // manter na penúltima linha da grelha
        pos.X = 1;
        // deslocar o mapa
        if (_M.X > 0) {
            _M.X--;
            // desenhar jogador
            render(jogador);
            //TODO desenhar outros jogadores
        }
    }

    // manter primeira linha ...
    if (pos.X < 0) pos.X = 0;

    jogador.pos(pos.X, pos.Y);

    return *this;
}

Leinad &Leinad::up(Jogador &jogador)
{
    COORD pos = jogador.pos();
    pos.Y--;

    if (_colision(pos)) return *this;

    // existe mapa não visível e segunda linha da grelha
    if (_M.Y > 0 && pos.Y == 0) {
        // manter na penúltima linha da grelha
        pos.Y = 1;
        // deslocar o mapa
        if (_M.Y > 0) {
            _M.Y--;
            // desenhar jogador
            render(jogador);
            //TODO desenhar outros jogadores
        }
    }

    // manter primeira linha ...
    if (pos.Y < 0 ) pos.Y = 0;

    jogador.pos(pos.X, pos.Y);

    return *this;
}

Leinad &Leinad::down(Jogador &jogador)
{
    COORD pos = jogador.pos();
    pos.Y++;

    if (_colision(pos)) return *this;

    // existe mapa não visível e penúltima linha da grelha
    if (pos.Y + _M.Y < _map.Y -1 && pos.Y > _grelha->height() - 2) {
        // manter na penúltima linha ...
        pos.Y = _grelha->height() - 2;
        // deslocar o mapa
        if (pos.Y < _M.Y + _map.Y) {
            _M.Y++;
            // desenhar jogador
            render(jogador);
            //TODO desenhar outros jogadores
        }
    }

    // última linha da grelha
    else if (pos.Y > _grelha->height() - 1) pos.Y = _grelha->height() - 1;

    jogador.pos(pos.X, pos.Y);

    return *this;
}

void Leinad::_draw(CHAR_INFO ci, COORD c)
{
    WORD textColor = console.textColor();

    // move cursor to required position
    SetConsoleCursorPosition(console.output(), c);

    console.textColor(ci.Attributes);
    cout << (char) ci.Char.UnicodeChar;

    // restore console attributes
    console.textColor(textColor);
}

void Leinad::_info(COORD c)
{
    WORD textColor = console.textColor();
    COORD G = _grelha->offset();

    SetConsoleCursorPosition(console.output(), COORD{ 0, _screen.Y - 1 });
    console.textColor(console.GREEN | console.GREEN_FADE << 4);
    cout << "O(" << G.X << "," << G.Y << ")  ";// offset da grelha (em relação à consola)
    cout << "S(" << c.X + G.X << "," << c.Y + G.Y << ")  ";// posição na consola
    cout << "M(" << c.X + _M.X << "," << c.Y + _M.Y << ")  ";// posição no mapa
    cout << "P(" << c.X << "," << c.Y << ")  ";// jogador
    cout << "_M(" << _M.X << "," << _M.Y << ")  ";// grelha
    cout << "MAPA: " << _map.X << "*" << _map.Y << "  ";// tamanho do mapa

    // restore console attributes
    console.textColor(textColor);
}

Leinad &Leinad::drawPlayer(Jogador &jogador, bool flag)
{
    // mostrar status informação (por enquanto ... coordenadas)
    _info(jogador.pos());

    // posição na consola
    COORD pos = jogador.pos();
    pos.X += _grelha->offset().X;
    pos.Y += _grelha->offset().Y;

    // desenhar na consola
    if (flag) _draw(jogador.imagem(), pos);
    else _draw(_grelha->pos(jogador.pos()), pos);

    return *this;
}

Leinad &Leinad::drawCaixa(Caixa &caixa)
{
    for (int x = caixa.pos().X; x < caixa.pos().X + caixa.width(); x++) {
        for (int y = caixa.pos().Y; y < caixa.pos().Y + caixa.height(); y++) {
            //TODO ponto pertence à grelha do mapa?

            short X = x - _M.X, Y = y - _M.Y;
            if (!(X < 0) && !(X >= _grelha->width()) && !(Y < 0) && !(Y >= _grelha->height()))
                _grelha->pos(COORD{ X, Y }, caixa.ci());
        }
    }
    return *this;
}

Leinad &Leinad::init() {
    (*_painel).fill(' ', console.CYAN_FADE << 4).write(console.output());
    (*_barra).fill(' ', console.GREEN_FADE << 4).write(console.output());
    return render(dummie);
}

Leinad &Leinad::render(Jogador jogador)
{
    // setup grelha
    (*_grelha).fill('.', console.BLUE | console.BLUE_FADE << 4);

    // desenhar as caixas
    if (_caixas != nullptr) {
        for (Caixa caixa : _caixas->caixas(_M, 60, 30)) {
            drawCaixa(caixa);
        }
    }

    // escrever na consola
    (*_grelha).write(console.output());

    //TEMP mostrar o jogador
    drawPlayer(jogador);

    ////TODO desenhar outros jogadores
    //drawPlayer(jogador);// desenhar jogador

    return *this;
}

Leinad::Leinad(short largura, short altura, Grelha *grelha)
{
    // não mostrar o cursor
    console.hideCursor();
    // tamanho janela
    _screen.X = largura, _screen.Y = altura;
    console.screenSize(largura, altura);
    //
    _grelha = grelha;
    //DEFAULT posição da grelha no mapa é a origem
    _M = { 0, 0 };
    //DEFAULT mapa tem dimensão da grelha
    _map = _grelha->size();
    // painel
    _painel = new Grelha(16, _map.Y, COORD{ 0, 0 });
    // barra
    _barra = new Grelha(largura, 1, COORD{ 0, altura - 1 });
    //TESTE um jogador (Jogador serão carregados dum ficheiro)
    dummie.pos(30, 15).imagem('@', console.CYAN | console.BLUE_FADE << 4);
}

Leinad::~Leinad()
{
    delete _barra;
    delete _painel;
}

void Leinad::info(string msg)
{
    WORD textColor = console.textColor();

    console.cursorPosition(COORD{ 10, _screen.Y - 1 });
    //SetConsoleCursorPosition(console.output_handle(), COORD{ 10, _screen.Y - 1 });
    console.textColor(console.GREEN | console.GREEN_FADE << 4);
    cout << " < " << msg << ">   ";
    console.textColor(textColor);
}

// colisão com obstáculo
bool Leinad::_colision(COORD pos, char ch)
{
    if (_grelha->pos(pos).Char.UnicodeChar == ch) return true;
    return false;
}
