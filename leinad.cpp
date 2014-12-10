#include <iostream>
#include "leinad.h"

using namespace std;

Leinad &Leinad::move(Jogador &jogador)
{
    // ler input da consola
    ReadConsoleInput(console.input_handle(), &console.input_record, 1, &console.info);

    // evento do teclado
    if (console.input_record.EventType == KEY_EVENT && console.input_record.Event.KeyEvent.bKeyDown) {
        // apaga o jogador
        drawPlayer(jogador, false);

        // nova posição do Jogador
        switch (console.input_record.Event.KeyEvent.wVirtualKeyCode) {
        case VK_RIGHT:
            right(jogador);
            break;
        case VK_LEFT:
            left(jogador);
            break;
        case VK_UP:
            up(jogador);
            break;
        case VK_DOWN:
            down(jogador);
            break;
        default:;
        }
        // desenha o jogador
        drawPlayer(jogador, true);
    }

    // limpar o buffer de input da consola
    FlushConsoleInputBuffer(console.input_handle());

    // acorrentar ...
    return *this;
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
    if (pos.X > _grelha->width() - 1) pos.X = _grelha->width() - 1;

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
    if (pos.Y > _grelha->height() - 1) pos.Y = _grelha->height() - 1;

    jogador.pos(pos.X, pos.Y);

    return *this;
}

void Leinad::_draw(CHAR_INFO ci, COORD c)
{
    WORD textColor = console.textColor();

    // move cursor to required position
    SetConsoleCursorPosition(console.output_handle(), c);

    console.textColor(ci.Attributes);
    cout << (char) ci.Char.UnicodeChar;

    // restore console attributes
    console.textColor(textColor);
}

void Leinad::_info(COORD c)
{
    WORD textColor = console.textColor();
    COORD G = _grelha->offset();

    SetConsoleCursorPosition(console.output_handle(), COORD{ 0, _screen.Y - 1 });
    console.textColor(console.GREEN | console.GREEN_FADE << 4);
    cout << "O(" << G.X << "," << G.Y << ")  ";// offset da grelha (em relação à consola)
    cout << "S(" << c.X + G.X << "," << c.Y + G.Y << ")  ";// posição na consola
    cout << "M(" << c.X + _M.X << "," << c.Y + _M.Y << ")  ";// posição no mapa
    cout << "P(" << c.X << "," << c.Y << ")  ";// jogador
    cout << "_M( " << _M.X << "," << _M.Y << ")  ";// grelha
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

Leinad::Leinad(short largura, short altura, Grelha *grelha)
{
    // tamanho janela
    _screen.X = largura, _screen.Y = altura;
    console.screenSize(largura, altura);

    _grelha = grelha;

    //DEFAULT posição da grelha no mapa é a origem
    _M = { 0, 0 };

    //DEFAULT mapa tem dimensão da grelha
    _map = _grelha->size();

    //TODO init grelha
}

Leinad::~Leinad()
{
    //delete[] _sector;
}

void Leinad::info(string msg)
{
    WORD textColor = console.textColor();
    SetConsoleCursorPosition(console.output_handle(), COORD{ 10, _screen.Y - 1 });
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
