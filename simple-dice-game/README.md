# 🎲 Dice Game (C Program)

## 📘 Introduction / Description

The **Dice Game** is a simple command-line gambling game written in C.  
The player starts with a fixed balance and places bets on the outcome of a dice roll. The goal is to guess the correct number (between 1 and 6). If the guess is correct, the player wins triple the bet; otherwise, the bet amount is lost.

The game continues until the player decides to quit or runs out of money.

This project demonstrates:
- Basic C programming concepts
- Loops and conditional statements
- User input handling
- Random number generation
- Simple game logic

---

## ⚙️ Function Description

### `int gamble(int balance)`

This function contains the main game logic.

**Parameters:**
- `balance`: The player’s current balance.

**Functionality:**
- Displays the current balance.
- Prompts the player to enter a bet.
- Ensures the bet does not exceed the available balance.
- Asks the player to guess a number between 1 and 6.
- Simulates rolling a dice using a random number.
- Updates the balance based on whether the guess was correct.
- Repeats until the player quits or the balance reaches zero.

**Returns:**
- The final balance after the game ends.

---

### `int main()`

This is the program entry point.

**Functionality:**
- Initializes the starting balance to `$1000`.
- Displays a welcome message and game instructions.
- Calls the `gamble()` function to start the game.
- Prints the final balance when the game ends.

---

## 🎮 How to Play

1. Compile the program:
   ```bash
   gcc dice1.c -o dice1
2. Run the game:
    ```
    ./dice1
3. The game starts with a balance of $1000.
4. Enter the amount you want to bet:
    - Enter 0 to quit the game.
    - You cannot bet more than your current balance.
5. Guess a number between 1 and 6.
6. The dice is rolled:
    - If your guess matches the dice number, you win 3× your bet.
    - If not, you lose your bet amount.
7. The game continues until:
    - You choose to quit, or
    - Your balance reaches $0.

---

✅ Example
- Bet: $100
- Guess: 4
- Dice roll: 4
- Result: You win $300

---

🏁 Game Over
When the game ends, your final balance is displayed along with a thank-you message.

Enjoy the game and gamble responsibly! 🎉

---