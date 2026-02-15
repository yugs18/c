# getnextline (Simplified Version)

This project is a **learning implementation** of a simplified `get_next_line` function in C.

The goal is to understand:

- dynamic memory allocation
- pointers and pointer movement
- reading from file descriptors
- string termination
- handling newline and EOF

⚠️ This is **NOT** the final 42 `get_next_line` implementation.  
It is a simplified educational version.

---

## 📌 What the program does

The function:

```c
char *gnl(void);
```

This function reads one line from standard input (stdin) and returns it as a newly allocated string.

**Behavior:**

- Reads input one character at a time using `read()`
- Stops when:
  - newline (`\n`) is found
  - EOF is reached
  - buffer limit is reached
- Replaces newline with `\0`
- Returns a `malloc`'ed string
- Caller must `free()` the returned pointer

## 🧠 How it works

### 1️⃣ Buffer allocation

```c
s = p = malloc(BUFSIZE);
```

- `s` → start of the string (returned later)
- `p` → moving pointer used to write characters

### 2️⃣ Buffer initialization

The `zero()` function sets all bytes to 0 so the result is a valid C string.

### 3️⃣ Reading loop

```c
read(0, p, 1);
```

- Reads 1 byte from stdin
- Characters are written into the buffer
- Pointer moves forward after each character

### 4️⃣ Line ending detection

Stops when:

- newline (`\n`)
- carriage return (`\r`)
- end of file

### 5️⃣ Return value

- Returns `NULL` if nothing was read
- Returns the line otherwise

## 📦 Example

**Input:**

```
hello
world
```

**Program output:**

```
'hello'
'world'
```

## ⚠️ Limitations

This version differs from the real 42 `get_next_line`:

- Works only with stdin (fd = 0)
- Fixed maximum line size (BUFSIZE)
- Reads one byte at a time (inefficient)
- Does NOT keep leftover data between calls
- No static buffer
- Long lines are truncated

## 🚀 Possible Improvements

To make this closer to the real project:

- Read chunks using `BUFFER_SIZE`
- Use a static stash to keep leftovers
- Support any file descriptor
- Allow unlimited line length
- Split logic into helper functions
