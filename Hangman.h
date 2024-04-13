#ifndef Hangman_H
#define Hangman_H

#include <string>
#include <vector>
#include <map>

class Hangman {

    public:
        void ReadWordsFromFile();
        void DetermineSecretWord();
        void ObtainUserGuess();
        void Start();
        void Reset();
        void PlayAgain();

        void DrawHangman();
        void HeaderText();
        void DisplayStage();
        void PrintWAtCoord(std::string, std::string, bool = false);
        void PrintWAtCoord(std::string, std::vector<int>, std::string, bool = false);
        void PrintWSAAtCoord(std::string, std::vector<std::string>);

        bool CheckProgress();
        bool CheckSolutionGuess(std::string);
        std::string GetWordProgress();
        std::string GetAlphabetWithGuesses();

    private:
        std::string secret_word;
        std::string user_guess;
        std::string guesses;
        std::string word_progress;
        std::string word_progress_concact;
        std::string play_again= "y";
        std::string hangman_words_path = "./hangman_words_easy.txt";
        const std::string full_alphabet = "abcdefghijklmnopqrstuvwxyz";

        char play_again_input[10];
        
        int current_number_of_incorrect_guesses;
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
            {"secret_word", {8, 19}},
            {"remaining_letters", {10, 19}},
            {"guess_text", {12, 19}},
            {"empty_stage", {8, 3}},
            {"hangman_head", {10, 4}},
            {"header_text", {0, 0}},
            {"play_again", {14, 19}}
        };
        
};

#endif