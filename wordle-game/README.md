# Wordle (C Implementation)

## Introduction
This project is a simple command-line implementation of the popular **Wordle** game, written in the C programming language.  
The program randomly selects a 5-letter word from a word list and allows the player to guess the word within a limited number of attempts, providing colored feedback after each guess.

---

## Program Description
The game loads a list of valid 5-letter words from a file (`wordlist.txt`) and randomly selects one as the correct answer.  
The player is given **5 attempts** to guess the word.

After each guess:
- Letters in the **correct position** are shown in **green**
- Letters that exist in the word but are in the **wrong position** are shown in **yellow**
- Letters **not in the word** are shown in **red**

The game ends when the player either guesses the correct word or runs out of attempts.

---

## Function Description

### `main()`
Initializes the game, loads the word list, selects a random word, and controls the main game loop.

### `readfile(char *filename)`
Reads valid 5-letter words from a file and stores them in memory for later validation and random selection.

### `random_word()`
Selects and returns a random word from the loaded word list.

### `gameloop(char *correct)`
Handles one round of gameplay, including prompting the user, validating input, checking the guess, and updating game state.

### `validator(char *word)`
Validates user input by checking:
- The word length is exactly 5 characters
- The word exists in the word list

### `readline()`
Reads a single line of input from the user and removes the newline character.

### `cw(char *guess, char *word)`
Compares the guessed word with the correct word and returns the result for each character.

### `cc(char guess, int idx, char *word)`
Compares a single character of the guess against the correct word and determines its result (green, yellow, or red).

### `isin(char c, char *str)`
Checks whether a character exists anywhere in a string.

### `print_result(Result *res, char *guess, char *correct)`
Prints the guessed word with colored output indicating correctness.

### `prompt(char *correct_word)`
Displays the current progress and remaining number of attempts.

### `seed()`
Seeds the random number generator using the process ID.

---

## How to Play

1. Make sure `wordlist.txt` exists in the same directory as the program.
2. Compile the program:
   ```sh
   gcc wordle.c -o wordle
4. Enter a 5-letter word when prompted.
5. Use the color feedback to refine your next guess:
- Green: correct letter in the correct position
- Yellow: correct letter in the wrong position
- Red: letter not in the word
6. Guess the word within 5 attempts to win.

---

## Notes
- Only words present in wordlist.txt are accepted.
- The game uses ANSI escape codes, so it works best in terminals that support colored output.
- Duplicate-letter rules are simplified compared to the original Wordle game.

---