#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <limits>
#include <chrono>
#include <thread>

class NumberGuessingGame {
private:
    const int MIN_RANGE = 1;
    const int MAX_RANGE = 100;
    const int MAX_ATTEMPTS = 7;

    int secretNumber;
    int currentAttempts;

    void clearInputStream() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    bool isValidGuess(int guess) {
        return guess >= MIN_RANGE && guess <= MAX_RANGE;
    }

    void provideHint(int guess) {
        if (guess < secretNumber) {
            std::cout << "\033[33m[Hint] Too low! Aim higher.\033[0m\n";
        } else {
            std::cout << "\033[33m[Hint] Too high! Aim lower.\033[0m\n";
        }
    }

    void displayProgress() {
        std::cout << "\nAttempts left: ";
        for (int i = 0; i < currentAttempts; ++i) {
            std::cout << "\033[32mO \033[0m";
        }
        std::cout << "\n";
    }

    bool wantsToContinue() {
        char response;
        std::cout << "\nWant to play again? (y/n): ";
        std::cin >> response;
        return (response == 'y' || response == 'Y');
    }

    void printBanner() {
        std::cout << "\033[36m";
        std::cout << "====================================\n";
        std::cout << "      Welcome to Number Guessing    \n";
        std::cout << "====================================\n\033[0m";
    }

    void printGameOver() {
        std::cout << "\033[31m";
        std::cout << "========================\n";
        std::cout << "       GAME OVER!        \n";
        std::cout << "========================\n\033[0m";
    }

    void printWinScreen() {
        std::cout << "\033[32m";
        std::cout << "========================\n";
        std::cout << "      YOU WIN!         \n";
        std::cout << "========================\n\033[0m";
    }

public:
    void play() {
        do {
            srand(time(nullptr));
            secretNumber = (rand() % MAX_RANGE) + 1;
            currentAttempts = MAX_ATTEMPTS;
            
            printBanner();
            std::cout << "I've chosen a number between 1 and 100. Try to guess it!\n";

            while (currentAttempts > 0) {
                int guess;
                displayProgress();
                std::cout << "\033[34mEnter your guess: \033[0m";
                std::cin >> guess;

                if (!isValidGuess(guess)) {
                    std::cout << "\033[31mInvalid guess! Enter a number between 1 and 100.\033[0m\n";
                    continue;
                }

                if (guess == secretNumber) {
                    printWinScreen();
                    break;
                }

                provideHint(guess);
                --currentAttempts;
            }

            if (currentAttempts == 0) {
                printGameOver();
                std::cout << "The number was: " << secretNumber << "\n";
            }

        } while (wantsToContinue());

        std::cout << "\033[35mThanks for playing!\033[0m\n";
    }
};

int main() {
    NumberGuessingGame game;
    game.play();
    return 0;
}


