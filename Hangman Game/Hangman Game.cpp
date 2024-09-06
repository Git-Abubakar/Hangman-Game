#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // for all_of function

using namespace std;

vector<string> words = { "apple", "banana", "orange", "grape", "kiwi", "melon" };

string selectRandomWord() {
    int randomIndex = rand() % words.size();
    return words[randomIndex];
}

void displayInitialHangman() {
    cout << "   _______" << endl;
    cout << "   |     |" << endl;
    cout << "         |" << endl;
    cout << "         |" << endl;
    cout << "         |" << endl;
    cout << "         |" << endl;
    cout << "_________|" << endl;
}

void displayCurrentHangman(int incorrectGuesses) {
    const vector<string> stages = {
        "\n   _______"
        "\n   |     |"
        "\n         |"
        "\n         |"
        "\n         |"
        "\n         |"
        "\n_________|"
        "\n",
        "\n   _______"
        "\n   |     |"
        "\n   O     |"
        "\n         |"
        "\n         |"
        "\n         |"
        "\n_________|"
        "\n",
        "\n   _______"
        "\n   |     |"
        "\n   O     |"
        "\n   |     |"
        "\n         |"
        "\n         |"
        "\n_________|"
        "\n",
        "\n   _______"
        "\n   |     |"
        "\n   O     |"
        "\n  /|     |"
        "\n         |"
        "\n         |"
        "\n_________|"
        "\n",
        "\n   _______"
        "\n   |     |"
        "\n   O     |"
        "\n  /|\\    |"
        "\n         |"
        "\n         |"
        "\n_________|"
        "\n",
        "\n   _______"
        "\n   |     |"
        "\n   O     |"
        "\n  /|\\    |"
        "\n  /      |"
        "\n         |"
        "\n_________|"
        "\n",
        "\n   _______"
        "\n   |     |"
        "\n   O     |"
        "\n  /|\\    |"
        "\n  / \\    |"
        "\n         |"
        "\n_________|"
        "\n"
    };

    cout << stages[incorrectGuesses];
}

void displayHiddenWord(const string& word, const vector<char>& correctGuesses) {
    for (char letter : word) {
        if (find(correctGuesses.begin(), correctGuesses.end(), letter) != correctGuesses.end()) {
            cout << letter << " ";
        }
        else {
            cout << "_ ";
        }
    }
    cout << endl;
}

char takeUserInput(const vector<char>& guessedLetters) {
    char userInput;
    while (true) {
        cout << "Guess a letter: ";
        cin >> userInput;
        userInput = tolower(userInput);

        if (isalpha(userInput) && find(guessedLetters.begin(), guessedLetters.end(), userInput) == guessedLetters.end()) {
            break;
        }
        else {
            cout << "Invalid input. Please enter a single letter that you haven't guessed before." << endl;
        }
    }

    return userInput;
}

bool checkIfGuessedLetterIsCorrect(char userInput, const string& word) {
    return find(word.begin(), word.end(), userInput) != word.end();
}

void updateHangmanState(int incorrectGuesses) {
    displayCurrentHangman(incorrectGuesses);
}

void updateHiddenWordDisplay(const string& word, const vector<char>& correctGuesses) {
    displayHiddenWord(word, correctGuesses);
}

bool checkForGameOver(const string& word, const vector<char>& correctGuesses, int incorrectGuesses) {
    if (all_of(word.begin(), word.end(), [&](char letter) { return find(correctGuesses.begin(), correctGuesses.end(), letter) != correctGuesses.end(); })) {
        cout << "Congratulations! You guessed the word: " << word << endl;
        return true;
    }
    else if (incorrectGuesses == 6) {
        cout << "Game over! The word was: " << word << endl;
        return true;
    }
    return false;
}

void displayGameOutcome(bool playerWon) {
    if (playerWon) {
        cout << "Congratulations! You won!" << endl;
    }
    else {
        cout << "Game over! Better luck next time." << endl;
    }
}

bool playAgain() {
    char playAgainChoice;
    cout << "Do you want to play again? (y/n): ";
    cin >> playAgainChoice;
    return tolower(playAgainChoice) == 'y';
}

int main() {
    srand(static_cast<unsigned>(time(nullptr))); // Seed for random word selection

    do {
        
        string wordToGuess = selectRandomWord();
        vector<char> guessedLetters;
        int incorrectGuesses = 0;

        while (true) {
            displayInitialHangman();
            displayHiddenWord(wordToGuess, guessedLetters);

            char userInput = takeUserInput(guessedLetters);

            guessedLetters.push_back(userInput);

            if (checkIfGuessedLetterIsCorrect(userInput, wordToGuess)) {
                cout << "Good guess!" << endl;
            }
            else {
                incorrectGuesses++;
                cout << "Incorrect guess. Try again!" << endl;
            }

            updateHangmanState(incorrectGuesses);
            updateHiddenWordDisplay(wordToGuess, guessedLetters);

            if (checkForGameOver(wordToGuess, guessedLetters, incorrectGuesses)) {
                break;
            }
        }

        displayGameOutcome(all_of(wordToGuess.begin(), wordToGuess.end(), [&](char letter) { return find(guessedLetters.begin(), guessedLetters.end(), letter) != guessedLetters.end(); }));

    } while (playAgain());

    cout << "Thank you for playing Hangman! Goodbye!" << endl;

    return 0;
}
