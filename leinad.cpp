//
// Leinad
//
// description: School project for OOP (Object Oriented Programming)
// author: José Vieira Lisboa
// url: https://github.com/joselisboa/leinad
//
#include <iostream>
#include "leinad.h"
#include <fstream>
using namespace std;

namespace leinad
{
    string const NOME{ "leinad" };
    string desc = "Trabalho Pratico POO | ISEC 2014 | 21230536, Jose Vieira Lisboa";
}

BOOL Leinad::menu()
{
    console.cls(console.MAGENTA_FADE);

    int x = 0,  y = _screen.Y / 4;
    console.cursorPosition(COORD{ x, y }).textColor(15 | console.MAGENTA_FADE << 4);

    ifstream title("..\\leinad.txt");
    if (!title) {
        cout << "ERRO a abrir ficheiro\n";
        return 1;
    }

    char c;
    title >> std::noskipws;// não saltar whitespace
    while (title >> c) { cout << c; }

    x = (_screen.X - leinad::desc.length()) / 2, y = _screen.Y - 2;
    console.cursorPosition(COORD{ x, y }).textColor(13 | console.MAGENTA_FADE << 4);
    cout << leinad::desc;

    // esperar que se carregue uma tecla
    while (!console.ch());

    // descrição na consola
    console.cls(console.MAGENTA_FADE);
    x = (_screen.X - leinad::desc.length()) / 2, y = _screen.Y - 2;
    console.cursorPosition(COORD{ x, y }).textColor(13 | console.MAGENTA_FADE << 4);
    cout << leinad::desc;

    //TODO delegar esta tarefa a uma função
    bool play = true, enabled = false;
    COORD O = { (_screen.X - 6) / 2, _screen.Y / 4 };
    //
    auto menuHelper = [](Ze &console, COORD pos, WORD attr, string s)
    {
        console.cursorPosition(pos).textColor(attr);
        cout << (char)201 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)187 << endl;
        console.cursorPosition(COORD{ pos.X, ++pos.Y });
        cout << (char)186 << s << (char)186 << endl;
        console.cursorPosition(COORD{ pos.X, ++pos.Y });
        cout << (char)200 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)188 << endl;
        return 0;
    };
    //
    auto menuToggle = [&play, &enabled, &O, &menuHelper](Ze &console) {
        if (!enabled) {
            enabled = true;
            menuHelper(console, O, 1 | console.MAGENTA << 4, " PLAY ");
            return 0;
        }

        WORD attr0, attr1;
        if (play) attr0 = 1 | console.MAGENTA_FADE << 4, attr1 = 1 | console.MAGENTA << 4;
        else attr0 = 1 | console.MAGENTA << 4, attr1 = 1 | console.MAGENTA_FADE << 4;

        play = !play;
        menuHelper(console, O, attr0, " PLAY ");
        menuHelper(console, COORD{ O.X, O.Y + 4 }, attr1, " EXIT ");

        return 0;
    };
    // opções inicias do menu (desactivado)
    menuHelper(console, O, 1 | console.MAGENTA_FADE << 4, " PLAY ");
    menuHelper(console, COORD{ O.X, O.Y + 4 }, 1 | console.MAGENTA_FADE << 4, " EXIT ");
    //
    while (true) {
        switch (console.ch()) {
            case VK_UP:
            case VK_DOWN:
                menuToggle(console);
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
        drawPlayer(dummy, false);

        // nova posição do Jogador
        switch (console.input_record.Event.KeyEvent.wVirtualKeyCode) {
        case VK_RIGHT:
            right(dummy);
            break;
        case VK_LEFT:
            left(dummy);
            break;
        case VK_UP:
            up(dummy);
            break;
        case VK_DOWN:
            down(dummy);
            break;
        case 27: return false;
        default:;

        }
        // desenha o jogador
        drawPlayer(dummy, true);

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

Leinad &Leinad::caixas(string filename)
{
    _caixas = new Caixas;

    ifstream mapa(filename);
    if (!mapa) {
        cout << "> ERRO a abrir o ficheiro " << filename << endl;
        exit(1);
    }
    short x, y, width, height;
    char ch;
    int attr;
    while (mapa >> x) {
        mapa >> y, mapa >> width, mapa >> height, mapa >> ch, mapa >> attr;
        _caixas->caixa(COORD{ x, y }, width, height, ch, attr);
    }

    // redimencionar os limites de movimento do mapa
    _map = _caixas->size();
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

Leinad &Leinad::init()
{
    (*_painel).fill(' ', console.CYAN_FADE << 4).write(console.output());
    (*_barra).fill(' ', console.GREEN_FADE << 4).write(console.output());

    _dummy_panel();

    return render(dummy);
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

Leinad::Leinad(LEINAD const CONFIG)
{
    // não mostrar o cursor e configurar dimensão da consola
	console.hideCursor().screenSize(CONFIG.consola.dim.width, CONFIG.consola.dim.height);

    //TODO remove this usage
    // tamanho janela
	_screen.X = CONFIG.consola.dim.width, _screen.Y = CONFIG.consola.dim.height;

    //Grelha grelha(GRELHA_WIDTH, GRELHA_HEIGHT, GRELHA_OFFSET);
    //_grelha = new Grelha(config.grelha);
	_grelha = new Grelha(CONFIG.grelha.dim.width, CONFIG.grelha.dim.height, CONFIG.grelha.pos);

    //DEFAULT posição da grelha no mapa é a origem
    _M = { 0, 0 };

    //DEFAULT mapa tem dimensão da grelha
    _map = _grelha->size();

    // painel
    //_painel = new Grelha(config.painel);
    _painel = new Grelha(16, _map.Y, COORD{ 0, 0 });

    // barra
    //_barra = new Grelha(config.barra);
	_barra = new Grelha(CONFIG.consola.dim.width, 1, COORD{ 0, CONFIG.consola.dim.height - 1 });

    //TESTE um jogador (Jogador serão carregados dum ficheiro)
    dummy.pos(30, 15).imagem('@', console.CYAN | console.BLUE_FADE << 4);

    // carregar o mapa
	caixas(CONFIG.mapa);
}

Leinad::~Leinad()
{
    delete _barra, _painel, _grelha;
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

//TEMP dummy panel
//TODO usar Grelha painel
void Leinad::_dummy_panel()
{
    console.paintString("DummyPanel", COORD{ 3, 1 }, console.RED_FADE | 8 << 4);

    int y = 4;

    console.paintString("Leinad 3", COORD{ 3, 1 + y }, 15 | console.CYAN_FADE << 4);
    console.cursorPosition(COORD{ 3, 2 + y }).background(7);
    cout << (char)3 << "   100%";
    console.cursorPosition(COORD{ 3, 3 + y }).background(7);
    cout << "$   3/50";
    console.cursorPosition(COORD{ 3, 4 + y }).background(7);
    cout << "?  11/35";
    console.cursorPosition(COORD{ 3, 5 + y }).background(7);
    cout << "!   1/16";

    console.paintString("Leinads", COORD{ 3, 7 + y }, 1 | console.CYAN_FADE << 4);
    console.cursorPosition(COORD{ 3, 8 + y }).background(8);
    cout << "$  12/50";
    console.cursorPosition(COORD{ 3, 9 + y }).background(8);
    cout << "?  20/35";
    console.cursorPosition(COORD{ 3, 10 + y }).background(8);
    cout << "!   4/16";

    console.paintString("Rivals", COORD{ 3, 12 + y }, 1 | console.CYAN_FADE << 4);
    console.cursorPosition(COORD{ 3, 13 + y }).background(8);
    cout << "$  21/50";
    console.cursorPosition(COORD{ 3, 14 + y }).background(8);
    cout << "?  15/35";
    console.cursorPosition(COORD{ 3, 15 + y }).background(8);
    cout << "!  14/16";
}
