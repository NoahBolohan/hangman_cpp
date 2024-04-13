#include <iostream>
#include "Hangman.h"
#include "Windows.h"

int main(int argc, char* argv[])
{
	Hangman hangman;

	//WINDOW* local_win;
	initscr();
	hangman.HeaderText();
	//local_win = create_newwin(10, 14, 7, 0);
	hangman.DisplayStage();
	hangman.Start();
	endwin();

	return 0;
}
