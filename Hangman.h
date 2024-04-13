#ifndef Hangman_H
#define Hangman_H

#include <string>
#include <vector>
#include <map>
#include <pdcurses/curses.h>

class Hangman {

    public:
        Hangman(WINDOW*, WINDOW*, WINDOW*);

        void ReadWordsFromFile();
        void DetermineSecretWord();
        void ObtainUserGuess();
        void Start();
        void Reset();
        void PlayAgain();

        void DrawHangman();
        void WHeaderText();
        void WDisplayStage();
        void WPrintWAtCoord(WINDOW*, std::string, std::string, bool = false);
        void WPrintWAtCoord(WINDOW*, std::string, std::vector<int>, std::string, bool = false);
        void WPrintWSAAtCoord(WINDOW*, std::string, std::vector<std::string>);

        void refresh_wins();
        void refresh_wins(std::vector<WINDOW*>);

        bool CheckProgress();
        bool CheckSolutionGuess(std::string);
        std::string GetWordProgress();
        std::string GetAlphabetWithGuesses();

    private:
        WINDOW* header_win;
        WINDOW* stage_win;
        WINDOW* text_win;

        std::string secret_word;
        std::string user_guess;
        std::string guesses;
        std::string word_progress;
        std::string word_progress_concact;
        std::string play_again= "y";
        std::string hangman_words_path = "./hangman_words_easy.txt";
        const std::string full_alphabet = "abcdefghijklmnopqrstuvwxyz";

        char play_again_input[10] = "y";
        
        int current_number_of_incorrect_guesses = 0;
        int max_number_of_incorrect_guesses = 7;
        

        std::vector<std::string> list_of_words;
        std::vector<std::string> empty_stage = {
             "  _____ ",
             " |    | ",
             "      | ",
             "      | ",
             "      | ",
             "      | ",
             "______|_"
        };

        std::vector<std::string> header_text = {
            "Welcome to Hangman!",
            "",
            "Rules:",
            "------",
            "1. Guess one letter of the alphabet at a time.",
            "2. If you want to guess the solution, input the word 'guess'."
        };

        std::map < std::string, std::vector<int> > coords = {
            {"header_text", {1, 1}},

            {"secret_word", {1,2}},
            {"remaining_letters", {3,2}},
            {"guess_text", {5,2}},
            {"play_again", {7,2}},

            {"empty_stage", {1,3}},
            {"hangman_head", {3,4}}
        };
        
};

#endif