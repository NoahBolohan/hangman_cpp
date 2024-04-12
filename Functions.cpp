#include <iostream>
#include <fstream>
#include <string>
#include "Hangman.h"

void Hangman::read_list_of_words() {
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
        std::cerr << e.what() << std::endl;
        system("pause");
    }
}

void Hangman::determine_secret_word() {

    srand((unsigned int)time(NULL));
    std::vector<std::string> list_of_words = {
            "apple",
            "banana",
            "clementine",
            "durian",
            "egg",
            "fries",
            "gourd",
            "hamburger",
            "ice",
            "juice"
    };
    secret_word = list_of_words[rand() % list_of_words.size()];
}

void Hangman::obtain_user_guess() {

    std::string user_guess;

    bool successful_guess = false;

    std::cout << "Guess a letter (or enter \"guess\" to guess the word)! (Remaining letters: ";

    for (std::string::size_type i = 0; i < full_alphabet.size(); ++i) {

        if (guesses.find(full_alphabet[i]) == std::string::npos) {
            std::cout << full_alphabet[i];
        }
        else {
            std::cout << "_";
        }
    }

    std::cout << ")" << std::endl;

    while (!successful_guess) {
        std::cin >> user_guess;

        if (user_guess == "guess") {

            std::cout << std::endl << "Enter your guess:" << std::endl;
            std::cin >> user_guess;

            if (Hangman::check_solution_guess(user_guess)) {
                guesses = user_guess;
            }
            successful_guess = true;
        }
        else {
            if (user_guess.size() != 1) {
                std::cout << std::endl << "Your guess is not a single letter in the alphabet. Try again!" << std::endl;
            }
            else if (guesses.find(user_guess) != std::string::npos) {
                std::cout << std::endl << "You already guessed that. Try again!" << std::endl;
            }
            else {
                successful_guess = true;
            }

            std::cout << std::endl;

            guesses += user_guess;

            if (secret_word.find(user_guess) == std::string::npos) {
                ++current_number_of_incorrect_guesses;
            }
        }
    }
}

bool Hangman::check_solution_guess(std::string user_guess) {

    std::cout << std::endl;
    if (user_guess == secret_word) {
        return true;
    }
    else {
        ++current_number_of_incorrect_guesses;
        std::cout << "Incorrect guess! The secret word is not \"" << user_guess << "\"." << std::endl << std::endl;
        return false;
    }
}

std::string Hangman::get_word_progress() {

    std::string word_progress = "";

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

bool Hangman::check_progress() {

    bool progress_bool = true;

    for (std::string::size_type i = 0; i < secret_word.size(); ++i) {

        if (guesses.find(secret_word[i]) == std::string::npos) {
            progress_bool = false;
        }
    }

    return progress_bool;
}

void Hangman::draw_hangman() {
    switch (current_number_of_incorrect_guesses) {
        case 1:
            std::cout << "  _____ " << std::endl;
            std::cout << " |    | " << std::endl;
            std::cout << " O    | " << std::endl;
            std::cout << "      | " << std::endl;
            std::cout << "      | " << std::endl;
            std::cout << "      | " << std::endl;
            std::cout << "______|_" << std::endl;
            break;
        case 2:
            std::cout << "  _____ " << std::endl;
            std::cout << " |    | " << std::endl;
            std::cout << " O    | " << std::endl;
            std::cout << " |    | " << std::endl;
            std::cout << "      | " << std::endl;
            std::cout << "      | " << std::endl;
            std::cout << "______|_" << std::endl;
            break;
        case 3:
            std::cout << "  _____ " << std::endl;
            std::cout << " |    | " << std::endl;
            std::cout << " O    | " << std::endl;
            std::cout << "/|    | " << std::endl;
            std::cout << "      | " << std::endl;
            std::cout << "      | " << std::endl;
            std::cout << "______|_" << std::endl;
            break;
        case 4:
            std::cout << "  _____ " << std::endl;
            std::cout << " |    | " << std::endl;
            std::cout << " O    | " << std::endl;
            std::cout << "/|\\   | " << std::endl;
            std::cout << "      | " << std::endl;
            std::cout << "      | " << std::endl;
            std::cout << "______|_" << std::endl;
            break;
        case 5:
            std::cout << "  _____ " << std::endl;
            std::cout << " |    | " << std::endl;
            std::cout << " O    | " << std::endl;
            std::cout << "/|\\   | " << std::endl;
            std::cout << " |    | " << std::endl;
            std::cout << "      | " << std::endl;
            std::cout << "______|_" << std::endl;
            break;
        case 6:
            std::cout << "  _____ " << std::endl;
            std::cout << " |    | " << std::endl;
            std::cout << " O    | " << std::endl;
            std::cout << "/|\\   | " << std::endl;
            std::cout << " |    | " << std::endl;
            std::cout << "/     | " << std::endl;
            std::cout << "______|_" << std::endl;
            break;
        case 7:
            std::cout << "  _____ " << std::endl;
            std::cout << " |    | " << std::endl;
            std::cout << " O    | " << std::endl;
            std::cout << "/|\\   | " << std::endl;
            std::cout << " |    | " << std::endl;
            std::cout << "/ \\   | " << std::endl;
            std::cout << "______|_" << std::endl;
            break;
        default: 
            std::cout << "  _____ " << std::endl;
            std::cout << " |    | " << std::endl;
            std::cout << "      | " << std::endl;
            std::cout << "      | " << std::endl;
            std::cout << "      | " << std::endl;
            std::cout << "      | " << std::endl;
            std::cout << "______|_" << std::endl;
    }
}

void Hangman::start_game() {

    Hangman::reset_game();

    std::cout << "Welcome to Hangman!" << std::endl << std::endl;
    std::cout << "Rules:" << std::endl;
    std::cout << "------" << std::endl;
    std::cout << "1. Guess one letter in the alphabet at a time." << std::endl;
    std::cout << "2. If you want to guess the solution, input the word 'guess'." << std::endl << std::endl;

    std::cout << "Determining the secret word..." << std::endl;

    Hangman::determine_secret_word();

    std::string word_progress;
    std::string word_progress_concact;

    while (current_number_of_incorrect_guesses < max_number_of_incorrect_guesses) {

        Hangman::draw_hangman();
        std::cout << "Secret word progress: " << Hangman::get_word_progress() << std::endl;

        Hangman::obtain_user_guess();

        if (Hangman::check_progress()) {
            std::cout << "You win! Woo-hoo! The word was: " << secret_word << std::endl << std::endl;
            break;
        }
    }

    if (current_number_of_incorrect_guesses >= max_number_of_incorrect_guesses) {
        Hangman::draw_hangman();
        std::cout << "Better luck next time! The secret word was \"" << secret_word << ".\"" << std::endl;
    }
}

void Hangman::reset_game() {

    guesses = "";
    current_number_of_incorrect_guesses = 0;
}