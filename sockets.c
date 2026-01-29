/* sockets.c */
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define IP "142.250.66.4" // www.google.com
#define PORT 80 // HTTP port

int main() {
    int s;
    struct sockaddr_in sock; // Define socket address structure
    char buf[512]; // Buffer to store received data
    char *data; // Pointer for request data

    data = "HEAD / HTTP/1.1\n\n"; // HTTP HEAD request

    s = socket(AF_INET, SOCK_STREAM, 0); // Create a TCP socket
    if (s < 0) {
        printf("Socket creation failed\n");
        return -1;
    }

    sock.sin_addr.s_addr = inet_addr(IP); // Set IP address
    sock.sin_port = htons(PORT); // Set port number
    sock.sin_family = AF_INET; // Set address family

    if (connect(s, (struct sockaddr *)&sock, sizeof(struct sockaddr_in)) != 0) { // Connect to server
        printf("Connection to %s:%d failed\n", IP, PORT);
        close(s);
        return -1;
    }

    write(s, data, strlen(data)); // Send HTTP HEAD request
    read(s, buf, 511); // Read response
    close(s); // Close the socket

    printf("Received data:\n%s\n", buf);
    return 0;
}
