/* dice1.c*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int gamble(int balance) {
    int bet, guess, dice;

    printf("Starting the game...\n");
    sleep(1);
    while(1) {
        if (balance <= 0) { // Check if the player has money left
            printf("You have no more money to bet. Game over!\n");
            break;
        }
        printf("Your current balance is $%d\n", balance);
        sleep(.3);
        printf("Enter your bet (zero to quit): ");
        sleep(.3);
        scanf("%d", &bet); // Get the player's bet
        if (bet == 0) { // Player chooses to quit
            printf("Thanks for playing! You leave with $%d\n", balance);
            break;
        }
        if (bet > balance) { // Check if the bet is valid
            printf("You cannot bet more than your current balance.\n");
            continue;
        }
        while(1) { // Get a valid guess from the player
            printf("Guess a number between 1 and 6: ");
            scanf("%d", &guess); // Get the player's guess
            if (guess < 1 || guess > 6) { // Validate the guess
                printf("Invalid guess! Please choose a number between 1 and 6.\n");
                continue;
            }
            break;
        }
        sleep(.3);
        printf("Rolling the dice...\n");
        sleep(2);
        dice = (rand() % 6) + 1; // Roll the dice
        printf("The dice shows: %d\n", dice);
        sleep(.5);
        if (guess == dice) { // Check if the guess is correct
            balance += bet * 3; // Player wins triple the bet
            printf("Congratulations! You guessed correctly and won $%d!\n", bet * 3);
        } else {
            balance -= bet; // Player loses the bet
            printf("Sorry, you guessed wrong. You lost $%d.\n", bet);
        }
        sleep(1);
    }
    return balance; // Return the final balance
}

int main() {
    int balance;

    balance = 1000; // Initial balance
    printf("Welcome to the Dice Game!\n");
    sleep(1);
    printf("Your starting balance is $%d\n", balance);
    sleep(1);
    printf("You can bet on a number between 1 and 6.\n");
    sleep(2);
    balance = gamble(balance); // Start the gambling game
    sleep(1);
    printf("Game over! Your final balance is $%d\n", balance);
    printf("Thanks for playing with us!!!\n");
    return 0;
}