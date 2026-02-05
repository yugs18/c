# C Programming Repository

A collection of my C programming work, including practice programs and small projects.

## Practice Programs

## Practice Programs/Concepts

- Hello World  
- Reading  
- Scanf  
- Integers  
- Decimal Numbers  
- Float  
- Errors  
- While Loops  
- If Statements  
- Functions  
- Random  
- Sleep  
- Countdown 
- Struct  
- Switch  
- Pointers  
- For Loops  
- References  
- Malloc  
- Sockets (Client)  
- Sockets (Server)  

---

## Projects

### 🎲 Simple Dice Game
A command-line gambling game written in C where the player bets money on the outcome of a dice roll. The player wins triple the bet on a correct guess and loses the bet on an incorrect one. The game continues until the player quits or runs out of money.

**Main Points:**
- Uses random number generation
- Implements loops and conditional logic
- Handles user input and validation
- Demonstrates basic game logic and state management

---

### 🟩 Wordle Game
A command-line implementation of the Wordle game written in C. The program selects a random 5-letter word from a word list, and the player has limited attempts to guess it, receiving colored feedback after each guess.

**Main Points:**
- File handling for loading word lists
- String manipulation and validation
- Use of structs and functions
- ANSI color output for feedback
- Game loop and input validation

---

### Toralize (SOCKS4 Tor Redirector)

A Linux shared library written in C that transparently routes outbound TCP connections through the Tor network by intercepting the connect() system call using LD_PRELOAD. The project implements the SOCKS4 protocol and redirects traffic without modifying the target application’s source code.

**Main Points:**
- Uses LD_PRELOAD to hijack the libc connect() function
- Implements the SOCKS4 CONNECT handshake
- Redirects traffic through Tor’s SOCKS proxy (127.0.0.1:9050)
- Employs dynamic linking (dlsym, RTLD_NEXT) to call the real connect()
- Uses dup2() to seamlessly replace the original socket
- Demonstrates low-level networking, proxy protocols, and runtime function interposition
- Highlights limitations of SOCKS4 with modern HTTPS and DNS resolution

---