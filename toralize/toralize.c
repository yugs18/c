/* toralize.c - SOCKS4 Tor redirection
 *
 * This file overrides the libc connect() function using LD_PRELOAD.
 * Any program calling connect() will be transparently redirected
 * through the Tor SOCKS4 proxy running on localhost:9050.
 */

#include "toralize.h"

/*
 * create_request()
 * ----------------
 * Builds a SOCKS4 request packet using the original destination
 * address supplied to connect().
 *
 * sock2 -> original destination (IP + port) requested by the program
 *
 * Returns:
 *   Pointer to a dynamically allocated SOCKS4 request structure.
 */
Req *create_request(struct sockaddr_in *sock2) {

    // Allocate memory for the SOCKS4 request structure
    Req *req = malloc(request_size);

    // SOCKS protocol version (must be 4 for SOCKS4)
    req->vn = 4;

    // Command code: 1 means CONNECT
    req->cd = 1;

    // Destination port (already in network byte order)
    req->dstport = sock2->sin_port;

    // Destination IP address (network byte order)
    req->dstip = sock2->sin_addr.s_addr;

    // USERID field required by SOCKS4
    // It is not authenticated here, but must exist
    strncpy(req->userid, USERNAME, sizeof(req->userid) - 1);

    return req;
}

/*
 * connect()
 * ---------
 * This function overrides the libc connect() function.
 *
 * Instead of connecting directly to the destination, it:
 * 1. Connects to the Tor SOCKS proxy
 * 2. Sends a SOCKS4 request containing the real destination
 * 3. Replaces the original socket with the Tor socket
 *
 * Parameters:
 *   s2      -> original socket file descriptor
 *   sock2   -> original destination address
 *   addrlen -> size of destination address
 */
int connect(int s2, const struct sockaddr *sock2, socklen_t addrlen) {

    int s;                          // Socket used to connect to Tor
    struct sockaddr_in sock;        // Tor proxy address
    Req *req;                       // SOCKS4 request

    char buffer[response_size];     // Buffer to store SOCKS4 response
    Res *res;                       // Parsed SOCKS4 response
    int success;

    /*
     * Function pointer to the real libc connect().
     * RTLD_NEXT ensures we bypass our overridden version
     * and call the actual system implementation.
     */
    int (*p)(int, const struct sockaddr *, socklen_t);
    p = dlsym(RTLD_NEXT, "connect");

    /*
     * Create a new TCP socket that will connect to the Tor proxy.
     * This socket is separate from the original application socket.
     */
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0)
        return -1;

    /*
     * Configure Tor SOCKS proxy address:
     *  - IPv4
     *  - Port 9050 (Tor default)
     *  - IP 127.0.0.1 (localhost)
     */
    sock.sin_family = AF_INET;
    sock.sin_port = htons(TORALIZE_PORT);
    sock.sin_addr.s_addr = inet_addr(LOCALHOST_IP);

    /*
     * Connect to the Tor SOCKS proxy using the real connect().
     * Using p() avoids infinite recursion.
     */
    if (p(s, (struct sockaddr *)&sock, sizeof(sock))) {
        close(s);
        return -1;
    }

    /*
     * Build a SOCKS4 request using the original destination
     * and send it to the Tor proxy.
     */
    req = create_request((struct sockaddr_in *)sock2);
    write(s, req, request_size);

    /*
     * Read the SOCKS4 response from Tor.
     * The response indicates whether the connection was granted.
     */
    read(s, buffer, response_size);
    res = (Res *)buffer;

    /*
     * SOCKS4 success code:
     *   90 -> Request granted
     * Any other value indicates failure.
     */
    if (res->cd != 90) {
        free(req);
        close(s);
        return -1;
    }

    /*
     * dup2() replaces the original socket (s2) with the Tor socket (s).
     * After this call, the application continues to use s2,
     * but all traffic actually flows through Tor.
     */
    dup2(s, s2);

    // Free allocated request structure
    free(req);

    // Return success to the calling application
    return 0;
}
