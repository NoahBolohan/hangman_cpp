#include <string>
#include <vector>
#include <stdexcept>
#include "Windows.h"
#include "Hangman.h"

void Hangman::HeaderText() {
	PrintWSAAtCoord("header_text", header_text);
}

void Hangman::DisplayStage() {
	PrintWSAAtCoord("empty_stage", empty_stage);
}

void Hangman::DrawHangman() {
	switch (current_number_of_incorrect_guesses) {
	case 7:
		PrintWAtCoord("hangman_head", { 3,1 }, std::string("\\"));
	case 6:
		PrintWAtCoord("hangman_head", { 3,-1 }, std::string("/"));
	case 5:
		PrintWAtCoord("hangman_head", { 2,0 }, std::string("|"));
	case 4:
		PrintWAtCoord("hangman_head", { 1,1 }, std::string("\\"));
	case 3:
		PrintWAtCoord("hangman_head", { 1,-1 }, std::string("/"));
	case 2:
		PrintWAtCoord("hangman_head", { 1,0 }, std::string("|"));
	case 1:
		PrintWAtCoord("hangman_head", std::string("O"));
	}
}

void Hangman::PrintWAtCoord(std::string coord_name, std::string line, bool clear_line) {
	try {
		if (coords.find(coord_name) == coords.end()) {
			throw std::invalid_argument(coord_name + " not in coords keys");
		}
		if (clear_line) {
			move(
				coords[coord_name].at(0),
				coords[coord_name].at(1)
			);
			clrtoeol();
		}

		mvprintw(
			coords[coord_name].at(0),
			coords[coord_name].at(1),
			line.c_str()
		);
		move(
			coords[coord_name].at(0),
			coords[coord_name].at(1) + line.size()
		);
	}

	catch (const std::invalid_argument& e) {
		PrintWAtCoord("guess_text", e.what(), true);
		getch();
	}
	
}

void Hangman::PrintWAtCoord(std::string coord_name, std::vector<int> offset, std::string line, bool clear_line) {
	try {
		if (coords.find(coord_name) == coords.end()) {
			throw std::invalid_argument(coord_name + " not in coords keys");
		}
		if (clear_line) {
			move(
				coords[coord_name].at(0) + offset.at(0),
				coords[coord_name].at(1) + offset.at(1)
			);
			clrtoeol();
		}
		
		mvprintw(
			coords[coord_name].at(0) + offset.at(0),
			coords[coord_name].at(1) + offset.at(1),
			line.c_str()
		);
		move(
			coords[coord_name].at(0) + offset.at(0),
			coords[coord_name].at(1) + offset.at(1) + line.size()
		);
	}

	catch (const std::invalid_argument& e) {
		PrintWAtCoord("guess_text", e.what(), true);
		getch();
	}
}

void Hangman::PrintWSAAtCoord(std::string coord_name, std::vector<std::string> lines) {
	try {
		if (coords.find(coord_name) == coords.end()) {
			throw std::invalid_argument(coord_name + " not in coords keys");
		}
		mvprintw_sa(
			coords[coord_name].at(0),
			coords[coord_name].at(1),
			lines
		);
		move(
			coords[coord_name].at(0) + lines.size(),
			coords[coord_name].at(1) + lines.back().size()
		);
	}

	catch (const std::invalid_argument& e) {
		PrintWAtCoord("guess_text", e.what(), true);
		getch();
	}
}