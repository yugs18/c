# Toralize — LD_PRELOAD based SOCKS4 Tor Redirector

Toralize is a Linux shared library that transparently redirects outbound TCP
connections through the **Tor network** by hijacking the `connect()` system call
using `LD_PRELOAD`.

It implements the **SOCKS4 protocol** and forces applications to route traffic
through Tor **without modifying their source code**.

---

## Features

- Intercepts `connect()` at runtime using `LD_PRELOAD`
- Redirects traffic through Tor’s SOCKS proxy (`127.0.0.1:9050`)
- Implements SOCKS4 CONNECT handshake
- Works with existing binaries (e.g. `curl`, `wget`)
- No application recompilation required

---

## How It Works (High Level)

1. A program calls `connect()`
2. Toralize intercepts the call
3. A new socket connects to Tor’s SOCKS proxy
4. A SOCKS4 request is sent with the original destination
5. On success, the original socket is replaced using `dup2()`
6. The application continues normally — unaware of Tor

---

## 📁 Project Structure
```
toralize/
├── toralize.c # connect() override and SOCKS4 logic
├── toralize.h # protocol structures and definitions
├── toralize.so # compiled shared library
├── Makefile
└── README.md
```

---

## Requirements

- Linux (glibc-based)
- GCC
- Tor installed and running
- Tor SOCKS proxy on port `9050`

---

## Build

Build using the Makefile:
```
make
```
Or compile manually:
```
gcc -fPIC -shared -D_GNU_SOURCE toralize.c -o toralize.so -ldl
```

---
## Usage - Examples
```
toralize curl http://example.com
```
```
toralize curl https://api.ipify.org
```

---

## Limitations (Important)
- Implements SOCKS4, not SOCKS4a or SOCKS5
- DNS resolution happens locally, not through Tor
- Modern HTTPS websites (e.g. Google) may fail due to:
- TLS + SNI hostname requirements
- SOCKS4 protocol limitations
- Intended for educational and experimental use

---

## Why SOCKS4 Has HTTPS Issues

- SOCKS4 forwards only an IP address to the proxy.
- Modern HTTPS requires hostname-based routing (SNI).

- Tor expects:
    - SOCKS4a (hostname support), or
    - SOCKS5 (recommended)

- This project intentionally uses SOCKS4 to demonstrate:
    - Protocol internals
    - LD_PRELOAD interception
    - Low-level socket redirection

---

## Disclaimer
**This project is for learning only.**