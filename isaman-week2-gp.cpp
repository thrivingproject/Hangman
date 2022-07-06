/*
 * Christian Isaman
 * Compiler: Visual Studio
 * Language Standard: ISO C++20 Standard (/std:c++20)
 * OS: Windows 11
 * Feature 1: Display number of incorrect guesses after each turn.
 * Feature 2: Display a used letter board after each turn.
 */

#include <iostream>
#include <string>
#include <chrono>
using namespace std;

void hangman();

int main()
{
    cout << "H   H     A     N N    N    GGGG  M       M     A     N N    N" << endl;
    cout << "H   H    A A    N  N   N   G      M M   M M    A A    N  N   N" << endl;
    cout << "HHHHH   A   A   N   N  N  G  GGG  M   M   M   A   A   N   N  N" << endl;
    cout << "H   H  AAAAAAA  N    N N  G    G  M   M   M  AAAAAAA  N    N N" << endl;
    cout << "H   H A       A N     NN   GGGG   M   M   M A       A N     NN" << endl;

    hangman();

    return 0;
}

void hangman()
{
    bool debug;
    cout << "\nDebug? Enter one ('1') for yes or zero ('0') for no: ";
    cin >> debug;

    srand(time(0));

    // Variables for gameplay
    bool badGuess = true;
    bool displayLetter = true;
    string dict[] = { "apple", "pottery", "dance", "snake", "jeopordy",
                     "platform", "healthcare", "country", "skip", "ocean" };
    int guesses = 6;
    bool lose = true;
    char letter{};
    vector<char> usedLetters;
    string word = dict[rand() % 10];
    int wordLength = word.length();
    vector<char> wordLetters;

    // Use wordLetters to track which letters have and haven't been guessed
    for (int i = 0; i < wordLength; i++)
    {
        wordLetters.push_back(word[i]);
    }

    // Begin the game
    while (guesses)
    {
        if (debug) cout << "\nDEBUG word: " << word << endl; // Mode to debug

        // Display the initial board and updated board after each turn
        cout << endl;
        for (int i = 0; i < wordLength; i++)
        {
            displayLetter = true;
            for (auto j : wordLetters)
            {
                if (word[i] == j)
                {
                    displayLetter = false;
                }
            }
            if (displayLetter) cout << word[i] << " ";
            else cout << "_ ";
        }
        cout << endl;

        // Get user's guess
        cout << "\nGuess a letter : ";
        cin >> letter;
        usedLetters.push_back(letter);
        badGuess = true;  // Track whether or not user looses a guess

        // Remove guessed letter from vector and end game when vector empty
        for (int i = 0; i < wordLetters.size(); i++)
        {
            // Remove letter from vector if in word
            if (wordLetters[i] == letter)
            {
                wordLetters.erase(wordLetters.begin() + i);
                i--;  // Move back an index since letter deleted
                badGuess = false;  // User does not lose a guess
            }
        }

        // Subtract a guess if letter guess is not in word
        if (badGuess) guesses--;

        // Win and end game if user guesses all letters
        if (!wordLetters.size())
        {
            cout << "\nGG! You guessed correctly! You are brilliant!" << endl;
            lose = false;
            break;
        }

        // Display number of incorrect guesses
        cout << "\nIncorrect guesses: " << 6 - guesses << endl;

        // Display the letters already guessed
        cout << "Used letters: ";
        for (auto i : usedLetters)
        {
            cout << i << " ";
        }
        cout << endl;
    }

    // Display losing message
    cout << endl << "Word: " << word << endl;
    if (lose)
    {
        cout << "\nGame over! Please try again." << endl;
    }
}