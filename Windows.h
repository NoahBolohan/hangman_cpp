#ifndef WINDOWS_H
#define WINDOWS_H

#include <string>
#include <vector>
#include <pdcurses/curses.h>

WINDOW* create_newwin(int, int, int, int);

void destroy_win(WINDOW*);

void mvprintw_sa(int, int, std::vector<std::string>);

#endif