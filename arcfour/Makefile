# ============================================================
# Compiler and Flags Configuration
# ============================================================

# C compiler to use
CC = gcc

# General compilation flags:
# -O2     → Enable level 2 optimization (good performance without heavy compile time)
# -Wall   → Enable most warning messages (helps catch bugs)
CFLAGS = -O2 -Wall

# Position Independent Code flag:
# -fPIC   → Required when building shared libraries (.so files)
#           Generates code that can be loaded at any memory address.
PICFLAGS = -fPIC

# Linker flags for building shared libraries:
# -shared         → Produce a shared object (.so)
# -ldl            → Link against libdl (dynamic loader library)
# -D_GNU_SOURCE   → Enable GNU-specific extensions
LDFLAGS = -shared -ldl -D_GNU_SOURCE


# ============================================================
# Default Target
# ============================================================

# The first target in a Makefile is the default.
# Running `make` with no arguments builds everything listed here.
all: example arcfour.so


# ============================================================
# Build the "example" Executable
# ============================================================

# Target: example
# Depends on: example.o
# Meaning:
#   If example.o changes, rebuild example.
example: example.o arcfour.o
	$(CC) example.o arcfour.o -o example $(CFLAGS)

# Compile example.c into object file example.o
# -c  → Compile only (do not link)
example.o: example.c
	$(CC) -c example.c $(CFLAGS)


# ============================================================
# Build the Shared Library (arcfour.so)
# ============================================================

# Target: arcfour.so
# Depends on: arcfour.o
#
# This creates a shared library instead of a normal executable.
# Shared libraries are dynamically loaded at runtime.
arcfour.so: arcfour.o
	$(CC) arcfour.o -o arcfour.so $(CFLAGS) $(PICFLAGS) $(LDFLAGS)

# Compile arcfour.c into position-independent object file
# -fPIC is REQUIRED for shared libraries.
arcfour.o: arcfour.c
	$(CC) -c arcfour.c $(CFLAGS) $(PICFLAGS)


# ============================================================
# Clean Target
# ============================================================

# Remove all generated files.
# This does NOT remove source files.
# Use: make clean
clean:
	rm -f *.o *.so example
