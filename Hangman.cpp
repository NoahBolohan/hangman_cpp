#include <iostream>
#include "Hangman.h"
#include "Windows.h"

int main(int argc, char* argv[])
{
	WINDOW* header_win;
	WINDOW* stage_win;
	WINDOW* text_win;

	initscr();

	header_win = create_newwin(8, 64, 0, 1);
	stage_win = create_newwin(10, 14, 8, 1);
	text_win = create_newwin(10, 96, 8, 16);
	
	Hangman hangman(header_win, stage_win, text_win);

	hangman.WHeaderText();
	hangman.WDisplayStage();

	hangman.Start();

	return 0;
}
