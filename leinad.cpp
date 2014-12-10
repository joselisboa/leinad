#include <iostream>
#include "leinad.h"

using namespace std;

BOOL Leinad::menu()
{
    console.background(console.MAGENTA_FADE);
    system("cls");

    while (true) {

        // ler input da consola
        ReadConsoleInput(console.input_handle(), &console.input_record, 1, &console.info);
        console.cursorPosition(0, 0);

        // evento do teclado
        if (console.input_record.EventType == KEY_EVENT && console.input_record.Event.KeyEvent.bKeyDown) {
            switch (console.input_record.Event.KeyEvent.wVirtualKeyCode) {
            case VK_RIGHT:
                cout << "RIGHT";
                break;
            case VK_LEFT:
                cout << "LEFT";
                break;
            case VK_UP:
                cout << "UP";
                break;
            case VK_DOWN:
                cout << "DOWN";
                break;
            // SAIR (escape)
            case 27: return false;
            // CONTINUAR
            case 13: return true;
            default:
                cout << (char)console.input_record.Event.KeyEvent.wVirtualKeyCode;
            }
            cout << " (" << console.input_record.Event.KeyEvent.wVirtualKeyCode << ")    ";
        }

        // limpar o buffer de input da consola
        FlushConsoleInputBuffer(console.input_handle());
    }

    // sair normalmente ...
    return true;
}

BOOL Leinad::move()
{
    // ler input da consola
    ReadConsoleInput(console.input_handle(), &console.input_record, 1, &console.info);

    // evento do teclado
    if (console.input_record.EventType == KEY_EVENT && console.input_record.Event.KeyEvent.bKeyDown) {
        // apaga o jogador
        drawPlayer(dummie, false);

        // nova posi��o do Jogador
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
    FlushConsoleInputBuffer(console.input_handle());

    // sa�da normal ...
    return true;
}

Leinad &Leinad::right(Jogador &jogador)
{
    COORD pos = jogador.pos();
    pos.X++;

    if (_colision(pos)) return *this;

    // existe mapa n�o vis�vel e pen�ltima linha da grelha
    if (pos.X + _M.X < _map.X - 1 && pos.X > _grelha->width() - 2) {
        // manter na pen�ltima linha ...
        pos.X = _grelha->width() - 2;
        // deslocar o mapa
        if (pos.X < _M.X + _map.X) {
            _M.X++;
            // desenhar jogador
            render(jogador);
            //TODO desenhar outros jogadores
        }
    }

    // �ltima linha da grelha
    if (pos.X > _grelha->width() - 1) pos.X = _grelha->width() - 1;

    jogador.pos(pos.X, pos.Y);

    return *this;
}

Leinad &Leinad::left(Jogador &jogador)
{
    COORD pos = jogador.pos();
    pos.X--;

    if (_colision(pos)) return *this;

    // existe mapa n�o vis�vel e segunda linha da grelha
    if (_M.X > 0 && pos.X == 0) {
        // manter na pen�ltima linha da grelha
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

    // existe mapa n�o vis�vel e segunda linha da grelha
    if (_M.Y > 0 && pos.Y == 0) {
        // manter na pen�ltima linha da grelha
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

    // existe mapa n�o vis�vel e pen�ltima linha da grelha
    if (pos.Y + _M.Y < _map.Y -1 && pos.Y > _grelha->height() - 2) {
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
    else if (pos.Y > _grelha->height() - 1) pos.Y = _grelha->height() - 1;

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
    cout << "O(" << G.X << "," << G.Y << ")  ";// offset da grelha (em rela��o � consola)
    cout << "S(" << c.X + G.X << "," << c.Y + G.Y << ")  ";// posi��o na consola
    cout << "M(" << c.X + _M.X << "," << c.Y + _M.Y << ")  ";// posi��o no mapa
    cout << "P(" << c.X << "," << c.Y << ")  ";// jogador
    cout << "_M(" << _M.X << "," << _M.Y << ")  ";// grelha
    cout << "MAPA: " << _map.X << "*" << _map.Y << "  ";// tamanho do mapa

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

Leinad &Leinad::drawCaixa(Caixa &caixa)
{
    for (int x = caixa.pos().X; x < caixa.pos().X + caixa.width(); x++) {
        for (int y = caixa.pos().Y; y < caixa.pos().Y + caixa.height(); y++) {
            //TODO ponto pertence � grelha do mapa?

            short X = x - _M.X, Y = y - _M.Y;
            if (!(X < 0) && !(X >= _grelha->width()) && !(Y < 0) && !(Y >= _grelha->height()))
                _grelha->pos(COORD{ X, Y }, caixa.ci());
        }
    }
    return *this;
}

Leinad &Leinad::init() {
    (*_painel).fill(' ', console.CYAN_FADE << 4).write(console.output_handle());
    (*_barra).fill(' ', console.GREEN_FADE << 4).write(console.output_handle());
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
    (*_grelha).write(console.output_handle());

    //TEMP mostrar o jogador
    drawPlayer(jogador);

    ////TODO desenhar outros jogadores
    //drawPlayer(jogador);// desenhar jogador

    return *this;
}

Leinad::Leinad(short largura, short altura, Grelha *grelha)
{
    // n�o mostrar o cursor
    console.hideCursor();
    // tamanho janela
    _screen.X = largura, _screen.Y = altura;
    console.screenSize(largura, altura);
    //
    _grelha = grelha;
    //DEFAULT posi��o da grelha no mapa � a origem
    _M = { 0, 0 };
    //DEFAULT mapa tem dimens�o da grelha
    _map = _grelha->size();
    // painel
    _painel = new Grelha(16, _map.Y, COORD{ 0, 0 });
    // barra
    _barra = new Grelha(largura, 1, COORD{ 0, altura - 1 });
    //TESTE um jogador (Jogador ser�o carregados dum ficheiro)
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

// colis�o com obst�culo
bool Leinad::_colision(COORD pos, char ch)
{
    if (_grelha->pos(pos).Char.UnicodeChar == ch) return true;
    return false;
}
