/* wordle.txt
 * Simple Wordle-like game implemented in C.
 * The player has 5 attempts to guess a random 5-letter word.
 */

#include <stdio.h>
#include <unistd.h>     // getpid()
#include <stdlib.h>     // rand(), srand()
#include <string.h>     // strlen(), memset()
#include <stdbool.h>    // bool type
#include <assert.h>     // assert()

/* Result values for each guessed character */
#define ResultGreen     1   // correct letter, correct position
#define ResultYellow    2   // correct letter, wrong position
#define ResultRed       4   // letter not in the word

#define max             4169    // maximum number of words in wordlist

/* Validation input */
#define ValOk           0
#define ValBadinput     1
#define ValNoSuchWord   2

/* ANSI color codes for terminal output */
#define ClrRed      "\e[0;31m"
#define ClrGreen    "\e[0;32m"
#define ClrYellow   "\e[0;33m"
#define ClrStop     "\e[0m"

/* Type aliases */
typedef char ValResult;
typedef char Result;

/* Global variables */
static char words[max][5];   // word list (each word is 5 chars, no '\0')
bool continuation;           // controls main game loop
int rounds;                  // number of guesses used
bool corrects[5];            // tracks which positions are correct
bool win;                    // win flag

/* Function prototypes */
bool strcmp_(char *, char *);
ValResult validator(char *);
char *readline(void);
void prompt(char *);
void gameloop(char *);
void seed(void);
char *random_word(void);
int readfile(char *);
bool isin(char, char *);
void print_result(Result*, char *, char *);
Result *cw(char *, char *);
Result cc(char, int, char *);

bool strcmp_(char *str1, char *str2) {
    for (int i = 0; i < 5; i++) {
        if (str1[i] != str2[i]) {
            return false;
        }
    }
    return true;
}


/* Validate user input:
 * - must be exactly 5 letters
 * - must exist in the word list
 */
ValResult validator(char *word) {
    if (strlen(word) != 5) {
        return ValBadinput;
    }

    for (int i = 0; i < max; i++) {
        if (strcmp_(words[i], word)) {
            return ValOk;
        }
    }

    return ValNoSuchWord;
}


/* Display current progress and remaining attempts */
void prompt(char *correct_word) {
    for (int i = 0; i < 5; i++) {
        if (corrects[i]) {
            printf("%c", correct_word[i]);
        } else {
            printf("-");
        }
    }

    printf("\n\n%d> ", (5 - rounds));
    fflush(stdout);
}

/* Print colored result of a guess */
void print_result(Result *res, char *guess, char *correct) {
    for (int i = 0; i < 5; i++) {
        switch (res[i]) {
            case ResultGreen:
                printf("%s%c%s", ClrGreen, guess[i], ClrStop);
                break;
            case ResultYellow:
                printf("%s%c%s", ClrYellow, guess[i], ClrStop);
                break;
            case ResultRed:
                printf("%s%c%s", ClrRed, guess[i], ClrStop);
                break;
        }
    }
    printf("\n");
}

/* Pick a random word from the word list */
char *random_word() {
    int r = rand() % max;
    static char ret[8];

    for (int i = 0; i < 5; i++) {
        ret[i] = words[r][i];
    }
    ret[5] = 0; // null-terminate

    return ret;
}

/* Check if a character exists in a string */
bool isin(char c, char *str) {
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == c) {
            return true;
        }
    }
    return false;
}

/* Compare a single character of the guess */
Result cc(char guess, int idx, char *word) {
    if (guess == word[idx]) {
        corrects[idx] = true;
        return ResultGreen;
    } else if (isin(guess, word)) {
        return ResultYellow;
    } else {
        return ResultRed;
    }
}

/* Read word list from file */
int readfile(char *filename) {
    char buf[8];
    FILE *fd;
    int i = 0;

    fd = fopen(filename, "r");
    if (fd == NULL) {
        perror("fopen");
        return -1;
    }

    while (fgets(buf, 7, fd)) {
        int size = strlen(buf);

        if (size < 1) continue;

        size--;             // remove '\n'
        buf[size] = 0;

        if (size != 5) continue;

        for (int j = 0; j < 5; j++) {
            words[i][j] = buf[j];
        }

        i++;
        if (i >= max) break;
    }

    fclose(fd);
    return i;
}


/* Compare whole word guess */
Result *cw(char *guess, char *word) {
    static Result res[5];

    for (int i = 0; i < 5; i++) {
        res[i] = cc(guess[i], i, word);
    }

    return res;
}

/* Seed random number generator */
void seed() {
    srand(getpid());
}

/* Read user input */
char *readline() {
    static char buf[8];

    memset(buf, 0, 8);
    fgets(buf, 7, stdin);

    int size = strlen(buf);
    assert(size > 0);

    buf[size - 1] = 0; // remove newline
    return buf;
}


/* One iteration of the game */
void gameloop(char *correct) {
    char *input;
    Result *res;
    ValResult valres;
    int c = 0;

    prompt(correct);
    input = readline();
    valres = validator(input);

    if (valres == ValBadinput) {
        printf("Input must be 5 letters.\n\n");
        return;
    } else if (valres == ValNoSuchWord) {
        printf("No such word in wordlist.\n\n");
        rounds++;
        return;
    }

    res = cw(input, correct);

    for (int i = 0; i < 5; i++) {
        if (corrects[i]) c++;
    }

    print_result(res, input, correct);

    if (c == 5) {
        win = true;
        continuation = false;
        return;
    }

    rounds++;
    if (rounds > 4) {
        win = false;
        continuation = false;
    }
}

/* Program entry point */
int main(int argc, char **argv) {
    int n;
    char *p;

    seed();
    n = readfile("wordlist.txt");
    assert(n >= 0);

    memset(corrects, false, sizeof(corrects));

    printf("Welcome to Wordle!\n");
    printf("You have 5 attempts to guess the correct 5-letter word.\n\n");

    rounds = 0;
    win = false;

    p = random_word();

    continuation = true;
    while (continuation) {
        gameloop(p);
    }

    printf("The correct word was: %s\n", p);
    printf(win ? "You win!\n" : "You lose!\n");

    return 0;
}