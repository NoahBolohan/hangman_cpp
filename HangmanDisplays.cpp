#include <string>
#include <vector>
#include <stdexcept>
#include "Windows.h"
#include "Hangman.h"

void Hangman::WHeaderText() {
	WPrintWSAAtCoord(header_win, "header_text", header_text);
}

void Hangman::WDisplayStage() {
	WPrintWSAAtCoord(stage_win,"empty_stage", empty_stage);
}

void Hangman::DrawHangman() {
	switch (current_number_of_incorrect_guesses) {
	case 7:
		WPrintWAtCoord(stage_win, "hangman_head", { 3,1 }, std::string("\\"));
	case 6:
		WPrintWAtCoord(stage_win, "hangman_head", { 3,-1 }, std::string("/"));
	case 5:
		WPrintWAtCoord(stage_win, "hangman_head", { 2,0 }, std::string("|"));
	case 4:
		WPrintWAtCoord(stage_win, "hangman_head", { 1,1 }, std::string("\\"));
	case 3:
		WPrintWAtCoord(stage_win, "hangman_head", { 1,-1 }, std::string("/"));
	case 2:
		WPrintWAtCoord(stage_win, "hangman_head", { 1,0 }, std::string("|"));
	case 1:
		WPrintWAtCoord(stage_win, "hangman_head", std::string("O"));
	}
}

void Hangman::WPrintWAtCoord(WINDOW* window, std::string coord_name, std::string line, bool clear_line) {
	try {
		if (coords.find(coord_name) == coords.end()) {
			throw std::invalid_argument(coord_name + " not in coords keys");
		}
		if (clear_line) {
			wmove(
				window,
				coords[coord_name].at(0),
				coords[coord_name].at(1)
			);
			wclrtoeol(window);
		}

		mvwprintw(
			window,
			coords[coord_name].at(0),
			coords[coord_name].at(1),
			line.c_str()
		);
		wmove(
			window,
			coords[coord_name].at(0),
			coords[coord_name].at(1) + line.size()
		);
	}

	catch (const std::invalid_argument& e) {
		WPrintWAtCoord(text_win, "guess_text", e.what(), true);
		getch();
	}
	
}

void Hangman::WPrintWAtCoord(WINDOW* window, std::string coord_name, std::vector<int> offset, std::string line, bool clear_line) {
	try {
		if (coords.find(coord_name) == coords.end()) {
			throw std::invalid_argument(coord_name + " not in coords keys");
		}
		if (clear_line) {
			wmove(
				window,
				coords[coord_name].at(0) + offset.at(0),
				coords[coord_name].at(1) + offset.at(1)
			);
			wclrtoeol(window);
		}
		
		mvwprintw(
			window,
			coords[coord_name].at(0) + offset.at(0),
			coords[coord_name].at(1) + offset.at(1),
			line.c_str()
		);
		wmove(
			window,
			coords[coord_name].at(0) + offset.at(0),
			coords[coord_name].at(1) + offset.at(1) + line.size()
		);
	}

	catch (const std::invalid_argument& e) {
		WPrintWAtCoord(text_win, "guess_text", e.what(), true);
		getch();
	}
}

void Hangman::WPrintWSAAtCoord(WINDOW* window, std::string coord_name, std::vector<std::string> lines) {
	try {
		if (coords.find(coord_name) == coords.end()) {
			throw std::invalid_argument(coord_name + " not in coords keys");
		}
		mvwprintw_sa(
			window,
			coords[coord_name].at(0),
			coords[coord_name].at(1),
			lines
		);
		wmove(
			window,
			coords[coord_name].at(0) + lines.size(),
			coords[coord_name].at(1) + lines.back().size()
		);
	}

	catch (const std::invalid_argument& e) {
		WPrintWAtCoord(text_win, "guess_text", e.what(), true);
		getch();
	}
}

void Hangman::refresh_wins() {
	wrefresh(header_win);
	wrefresh(stage_win);
	wrefresh(text_win);
}

void Hangman::refresh_wins(std::vector<WINDOW*> wins_to_refresh) {
	for (auto win : wins_to_refresh) {
		wrefresh(win);
	}
}

void Hangman::reset_win(WINDOW* window) {
	werase(window);
	wborder(window, '|', '|', '-', '-', '*', '+', '+', '+');
	wrefresh(window);
}