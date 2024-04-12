/*
This is a practice attempt to create the game Hangman in C++.

Idea
----
The executable will have either a list of possible words or the functionality to generate a random word. A word will be chosen, which the user has to determine by guessing individual letters at a time. Initially, a number of blank spaces will be displayed, equal to the length of the word. If the guessed letter is contained in the word, all blank spaces in which that letter lies will be converted to the letter. If the letter is not contained in the word, a portion of a man will be displayed. Moreover, the entire alphabet will be displayed, and each guess will remove that letter from the alphabet. The game ends when the user guesses the entire word, or the man is complete.
*/

#include <iostream>
#include "Hangman.h"

int main() {

    Hangman hangman;

    std::string play_again = "y";

    while (play_again == "y") {

        //hangman.read_list_of_words();
        hangman.start_game();

        std::cout << "Would you like to play again? (y/n)" << std::endl;
        std::cin >> play_again;
        std::cout << std::endl;
    }

    system("pause");
}