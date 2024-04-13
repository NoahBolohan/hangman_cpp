#include <iostream>
#include <fstream>
#include <string>
#include "Windows.h"
#include "Hangman.h"

Hangman::Hangman(WINDOW* header_win_arg, WINDOW* stage_win_arg, WINDOW* text_win_arg) {
    header_win = header_win_arg;
    stage_win = stage_win_arg;
    text_win = text_win_arg;
}

void Hangman::ReadWordsFromFile() {
    try {
        std::ifstream file;
        std::string line;
        file.open(hangman_words_path);

        if (!file) {
            throw std::runtime_error("File failed to open.");
        }
        while (getline(file, line)) {
            list_of_words.push_back(line);
        }

        file.close();
    }
    catch (std::exception& e) {
        WPrintWAtCoord(text_win, "guess_text", e.what(), true);
        refresh_wins({ text_win });
        getch();
    }
}

void Hangman::DetermineSecretWord() {
    srand((unsigned int)time(NULL));
    secret_word = list_of_words[rand() % list_of_words.size()];
}

void Hangman::ObtainUserGuess() {

    char user_guess_ca[10];
    bool successful_guess = false;

    WPrintWAtCoord(text_win, "guess_text", "Guess a letter (or enter \"guess\" to guess the word)!: ", true);
    refresh_wins({ text_win });

    while (!successful_guess) {
        wgetstr(text_win, user_guess_ca);
        std::string user_guess = std::string(user_guess_ca);
        
        if (user_guess == "guess") {
            WPrintWAtCoord(text_win, "guess_text", "Enter your guess: ", true);
            refresh_wins({ text_win });
            wgetstr(text_win, user_guess_ca);
            std::string user_guess = std::string(user_guess_ca);

            if (Hangman::CheckSolutionGuess(user_guess)) {
                guesses = user_guess;
            }
            successful_guess = true;
        }

        else {
            if (user_guess.size() != 1) {
                WPrintWAtCoord(text_win, "guess_text", "Your guess is too long! Try a single character: ", true);
                refresh_wins({ text_win });
            }
            else {
                if (full_alphabet.find(user_guess) == std::string::npos) {
                    WPrintWAtCoord(text_win, "guess_text", "Your guess isn't a letter of the alphabet! Try again: ", true);
                    refresh_wins({ text_win });
                }
                else if (guesses.find(user_guess) != std::string::npos) {
                    WPrintWAtCoord(text_win, "guess_text", "You already guessed that! Try again: ", true);
                    refresh_wins({ text_win });
                }
                else {

                    guesses += user_guess;
                    successful_guess = true;
                }

                if ((successful_guess)&&(secret_word.find(user_guess) == std::string::npos)) {
                    ++current_number_of_incorrect_guesses;
                }
            }
        }
    }
}

bool Hangman::CheckSolutionGuess(std::string user_guess) {

    if (user_guess == secret_word) {
        return true;
    }
    else {
        ++current_number_of_incorrect_guesses;
        WPrintWAtCoord(text_win, "guess_text", "Incorrect guess! The secret word is not \"" + user_guess + "\".", true);
        refresh_wins({ text_win });
        return false;
    }
}

std::string Hangman::GetWordProgress() {

    word_progress = "";

    for (std::string::size_type i = 0; i < secret_word.size(); ++i) {

        if (guesses.find(secret_word[i]) != std::string::npos) {
            word_progress.push_back(secret_word[i]);
            word_progress += " ";
        }

        else {
            word_progress += "_ ";
        }
    }

    return word_progress;
}

std::string Hangman::GetAlphabetWithGuesses() {

    std::string alphabet;

    for (std::string::size_type i = 0; i < full_alphabet.size(); ++i) {

        if (guesses.find(full_alphabet[i]) == std::string::npos) {
            alphabet += full_alphabet[i];
        }
        else {
            alphabet += "_";
        }
    }

    return alphabet;
}

bool Hangman::CheckProgress() {

    bool progress_bool = true;

    for (std::string::size_type i = 0; i < secret_word.size(); ++i) {

        if (guesses.find(secret_word[i]) == std::string::npos) {
            progress_bool = false;
        }
    }

    return progress_bool;
}

void Hangman::Start() {

    while (play_again == "y") {
        WPrintWAtCoord(text_win, "play_again", "", true);
        Reset();
        ReadWordsFromFile();
        DetermineSecretWord();

        while (current_number_of_incorrect_guesses < max_number_of_incorrect_guesses) {

            DrawHangman();
            WPrintWAtCoord(text_win, "secret_word", "Secret word progress: " + GetWordProgress());
            WPrintWAtCoord(text_win, "remaining_letters", "Remaining letters: " + GetAlphabetWithGuesses());

            refresh_wins();

            ObtainUserGuess();

            if (CheckProgress()) {
                WPrintWAtCoord(text_win, "secret_word", "Secret word progress: " + GetWordProgress());
                WPrintWAtCoord(text_win, "guess_text", "You win! Woo-hoo! The word was: " + secret_word, true);

                refresh_wins({ text_win });
                break;
            }
        }

        if (current_number_of_incorrect_guesses >= max_number_of_incorrect_guesses) {
            DrawHangman();
            WPrintWAtCoord(text_win, "guess_text", "Better luck next time! The secret word was \"" + secret_word + ".\"", true);
            refresh_wins();
        }

        PlayAgain();
    }
}

void Hangman::Reset() {

    guesses = "";
    current_number_of_incorrect_guesses = 0;
    word_progress = "";
    word_progress_concact = "";
}

void Hangman::PlayAgain() {

    WPrintWAtCoord(text_win, "play_again", "Would you like to play again? (y\\n): ");
    wgetstr(text_win, play_again_input);

    play_again = std::string(play_again_input);
}