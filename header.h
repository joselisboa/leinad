#include <Windows.h>
#include <iostream>
#include <vector>
#include "leinad.h"

// Grelha
void testeGrelha()
{
	Grelha grelha(40, 20);// GRELHA.X, GRELHA.Y);
	grelha.testes();
	grelha.offset(COORD{ 21, 3 }).fill('?', Ze().RED_FADE).write(Ze().output_handle());
	grelha.offset(COORD{ 15, 5 }).fill('#', Ze().MAGENTA_FADE).write(Ze().output_handle());
}

// Ze
void testeZe()
{
	cout << "> Ze().textColor(Ze().YELLOW);"<< endl;
	Ze().textColor(Ze().YELLOW);
	cout << "> Ze().paintString(\"Jose Daniel\", COORD{ 5, 5 }, Ze().BLUE_FADE | Ze().CYAN_FADE << 4);" << endl;
	Ze().paintString("Jose Daniel", COORD{ 5, 5 }, Ze().BLUE_FADE | Ze().CYAN_FADE << 4);
	while (false) {
	  Ze().input();
	}
}
