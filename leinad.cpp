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

        // nova posi��o do Jogador
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

    //TODO verify grid
    pos.X++;
    if (_colision(pos)) return *this;

    // verificar que o jogador n�o sai dos limites
    if (pos.X > _grelha->width() -1){//   console.screen_info.srWindow.Right) {
        pos.X = _grelha->width() - 1;// console.screen_info.srWindow.Right;
    }

    jogador.pos(pos.X, pos.Y);

    return *this;
}

Leinad &Leinad::left(Jogador &jogador)
{
    COORD pos = jogador.pos();
    pos.X--;
    if (_colision(pos)) return *this;

    if (pos.X < console.screen_info.srWindow.Left)
        pos.X = console.screen_info.srWindow.Left;

    jogador.pos(pos.X, pos.Y);
    return *this;
}

Leinad &Leinad::up(Jogador &jogador)
{
    COORD pos = jogador.pos();
    pos.Y--;
    if (_colision(pos)) return *this;

    if (pos.Y < console.screen_info.srWindow.Top)
        pos.Y = console.screen_info.srWindow.Top;

    jogador.pos(pos.X, pos.Y);
    return *this;
}

Leinad &Leinad::down(Jogador &jogador)
{
    COORD pos = jogador.pos();
    pos.Y++;

    if (_colision(pos)) return *this;


	if (pos.Y + _M.Y < _map.Y -1)
	// pen�ltima linha da grelha
	if (pos.Y > _grelha->height() - 2) {
        // manter na pen�ltima linha ...
		pos.Y = _grelha->height() - 2;

		// deslocar o mapa
		if (pos.Y < _M.Y + _map.Y) {
            _M.Y++;
            // desenhar jogador
            render(jogador);
            //TODO desenhar outros jogadores
        }
    }

	// �ltima linha da grelha
	if (pos.Y > _grelha->height() - 1) {
		pos.Y = _grelha->height() - 1;
	}

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
    cout << "S(" << c.X + G.X << "," << c.Y + G.Y << ")  ";
    cout << "M(" << c.X + _M.X << "," << c.Y + _M.Y << ")  ";
    cout << "G(" << c.X << "," << c.Y << ")  ";
	cout << "MAPA: " << _map.X << "*" << _map.Y << "  ";

    // restore console attributes
    console.textColor(textColor);
}

Leinad &Leinad::drawPlayer(Jogador &jogador, bool flag)
{
    // mostrar status informa��o (por enquanto ... coordenadas)
    _info(jogador.pos());

    // posi��o na consola
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

    //DEFAULT posi��o da grelha no mapa � a origem
    _M = { 0, 0 };

    //DEFAULT mapa tem dimens�o da grelha
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

// colis�o com obst�culo
bool Leinad::_colision(COORD pos, char ch)
{
    if (_grelha->pos(pos).Char.UnicodeChar == ch) return true;
    return false;
}
