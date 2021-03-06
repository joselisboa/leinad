//
// Leinad
//
// description: School project for OOP (Object Oriented Programming)
// author: José Vieira Lisboa
// url: https://github.com/joselisboa/leinad
//
#include <Windows.h>
#include <fstream>
#include <iostream>
#include <vector>
#include "leinad.h"

// testa a classe Grelha
void testeGrelha()
{
    Grelha grelha({ { 40, 20 }, { 0, 0 } });
    grelha.testes();
    grelha.pos(COORD{ 21, 3 }).fill('?', Ze().RED_FADE).write(Ze().output());
    grelha.pos(COORD{ 15, 5 }).fill('#', Ze().MAGENTA_FADE).write(Ze().output());
}

// testa a classe Ze
void testeZe()
{
    cout << "> Ze().textColor(Ze().YELLOW);"<< endl;
    Ze().textColor(Ze().YELLOW);
    cout << "> Ze().paintString(\"Jose Daniel\", COORD{ 5, 5 }, Ze().BLUE_FADE | Ze().CYAN_FADE << 4);" << endl;
    Ze().paintString("Jose Daniel", COORD{ 5, 5 }, Ze().BLUE_FADE | Ze().CYAN_FADE << 4);
    while (false) {
        Ze()._input();
    }
}
