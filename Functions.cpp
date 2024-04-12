#include <iostream>
#include <fstream>
#include <string>
#include "Hangman.h"
using namespace std;

//void Hangman::read_list_of_words() {
//    try {
//        ifstream file;
//        string line;
//        file.open(hangman_words_path);
//
//        if (!file) {
//            throw runtime_error("File failed to open.");
//        }
//        while (getline(file, line)) {
//            list_of_words.push_back(line);
//        }
//
//        file.close();
//    }
//    catch (exception& e) {
//        cerr << e.what() << endl;
//        system("pause");
//    }
//}

void Hangman::determine_secret_word() {

    srand((unsigned int)time(NULL));
    //vector<string> list_of_words = {
    //        "apple",
    //        "banana",
    //        "clementine",
    //        "durian",
    //        "egg",
    //        "fries",
    //        "gourd",
    //        "hamburger",
    //        "ice",
    //        "juice"
    //};
    secret_word = list_of_words[rand() % list_of_words.size()];
}

void Hangman::obtain_user_guess() {

    string user_guess;

    bool successful_guess = false;

    cout << "Guess a letter (or enter \"guess\" to guess the word)! (Remaining letters: ";

    for (string::size_type i = 0; i < full_alphabet.size(); ++i) {

        if (guesses.find(full_alphabet[i]) == string::npos) {
            cout << full_alphabet[i];
        }
        else {
            cout << "_";
        }
    }

    cout << ")" << endl;

    while (!successful_guess) {
        cin >> user_guess;

        if (user_guess == "guess") {

            cout << endl << "Enter your guess:" << endl;
            cin >> user_guess;

            if (Hangman::check_solution_guess(user_guess)) {
                guesses = user_guess;
            }
            successful_guess = true;
        }
        else {
            if (user_guess.size() != 1) {
                cout << endl << "Your guess is not a single letter in the alphabet. Try again!" << endl;
            }
            else if (guesses.find(user_guess) != string::npos) {
                cout << endl << "You already guessed that. Try again!" << endl;
            }
            else {
                successful_guess = true;
            }

            cout << endl;

            guesses += user_guess;

            if (secret_word.find(user_guess) == string::npos) {
                ++current_number_of_incorrect_guesses;
            }
        }
    }
}

bool Hangman::check_solution_guess(string user_guess) {

    cout << endl;
    if (user_guess == secret_word) {
        return true;
    }
    else {
        ++current_number_of_incorrect_guesses;
        cout << "Incorrect guess! The secret word is not \"" << user_guess << "\"." << endl << endl;
        return false;
    }
}

string Hangman::get_word_progress() {

    string word_progress = "";

    for (string::size_type i = 0; i < secret_word.size(); ++i) {

        if (guesses.find(secret_word[i]) != string::npos) {
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

    for (string::size_type i = 0; i < secret_word.size(); ++i) {

        if (guesses.find(secret_word[i]) == string::npos) {
            progress_bool = false;
        }
    }

    return progress_bool;
}

void Hangman::draw_hangman() {
    switch (current_number_of_incorrect_guesses) {
        case 1:
            cout << "  _____ " << endl;
            cout << " |    | " << endl;
            cout << " O    | " << endl;
            cout << "      | " << endl;
            cout << "      | " << endl;
            cout << "      | " << endl;
            cout << "______|_" << endl;
            break;
        case 2:
            cout << "  _____ " << endl;
            cout << " |    | " << endl;
            cout << " O    | " << endl;
            cout << " |    | " << endl;
            cout << "      | " << endl;
            cout << "      | " << endl;
            cout << "______|_" << endl;
            break;
        case 3:
            cout << "  _____ " << endl;
            cout << " |    | " << endl;
            cout << " O    | " << endl;
            cout << "/|    | " << endl;
            cout << "      | " << endl;
            cout << "      | " << endl;
            cout << "______|_" << endl;
            break;
        case 4:
            cout << "  _____ " << endl;
            cout << " |    | " << endl;
            cout << " O    | " << endl;
            cout << "/|\\   | " << endl;
            cout << "      | " << endl;
            cout << "      | " << endl;
            cout << "______|_" << endl;
            break;
        case 5:
            cout << "  _____ " << endl;
            cout << " |    | " << endl;
            cout << " O    | " << endl;
            cout << "/|\\   | " << endl;
            cout << " |    | " << endl;
            cout << "      | " << endl;
            cout << "______|_" << endl;
            break;
        case 6:
            cout << "  _____ " << endl;
            cout << " |    | " << endl;
            cout << " O    | " << endl;
            cout << "/|\\   | " << endl;
            cout << " |    | " << endl;
            cout << "/     | " << endl;
            cout << "______|_" << endl;
            break;
        case 7:
            cout << "  _____ " << endl;
            cout << " |    | " << endl;
            cout << " O    | " << endl;
            cout << "/|\\   | " << endl;
            cout << " |    | " << endl;
            cout << "/ \\   | " << endl;
            cout << "______|_" << endl;
            break;
        default: 
            cout << "  _____ " << endl;
            cout << " |    | " << endl;
            cout << "      | " << endl;
            cout << "      | " << endl;
            cout << "      | " << endl;
            cout << "      | " << endl;
            cout << "______|_" << endl;
    }
}

void Hangman::start_game() {

    Hangman::reset_game();

    cout << "Welcome to Hangman!" << endl << endl;
    cout << "Rules:" << endl;
    cout << "------" << endl;
    cout << "1. Guess one letter in the alphabet at a time." << endl;
    cout << "2. If you want to guess the solution, input the word 'guess'." << endl << endl;

    cout << "Determining the secret word..." << endl;

    Hangman::determine_secret_word();

    string word_progress;
    string word_progress_concact;

    while (current_number_of_incorrect_guesses < max_number_of_incorrect_guesses) {

        Hangman::draw_hangman();
        cout << "Secret word progress: " << Hangman::get_word_progress() << endl;

        Hangman::obtain_user_guess();

        if (Hangman::check_progress()) {
            cout << "You win! Woo-hoo! The word was: " << secret_word << endl << endl;
            break;
        }
    }

    if (current_number_of_incorrect_guesses >= max_number_of_incorrect_guesses) {
        Hangman::draw_hangman();
        cout << "Better luck next time! The secret word was \"" << secret_word << ".\"" << endl;
    }
}

void Hangman::reset_game() {

    guesses = "";
    current_number_of_incorrect_guesses = 0;
}