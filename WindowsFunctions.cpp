#include <string>
#include <vector>
#include "Windows.h"
#include <pdcurses/curses.h>

WINDOW* create_newwin(int height, int width, int starty, int startx)
{
	WINDOW* local_win;

	local_win = newwin(height, width, starty, startx);
	wborder(local_win, '|', '|', '-', '-', '*', '+', '+', '+');
	wrefresh(local_win);
	return local_win;
}

void destroy_win(WINDOW* local_win)
{
	wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(local_win);
	delwin(local_win);
}

void mvprintw_sa(int y, int x, std::vector<std::string> texts)
{
	int i = 0;
	for (const std::string& text : texts) {
		mvprintw(y + i, x, text.c_str());
		i++;
	}
}

void mvwprintw_sa(WINDOW* window, int y, int x, std::vector<std::string> texts)
{
	int i = 0;
	for (const std::string& text : texts) {
		mvwprintw(window, y + i, x, text.c_str());
		i++;
	}
}