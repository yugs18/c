/* toralize.c */
#include "toralize.h"

// ./toralize.c <target_ip> <target_port>

int main(int argc, char *argv[]) {
    char *target_ip;
    int target_port, sockfd;

    struct sockaddr_in sock;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <target_ip> <target_port>\n", argv[0]);
        return -1;
    }
    target_ip = argv[1];
    target_port = atoi(argv[2]);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return -1;
    }

    sock.sin_family = AF_INET;
    sock.sin_port = htons(TORALIZE_PORT);
    sock.sin_addr.s_addr = inet_addr(LOCALHOST_IP);

    if (connect(sockfd, (struct sockaddr *)&sock, sizeof(sock))) {
        perror("Connection to Tor failed");
        close(sockfd);
        return -1;
    }

    printf("[*] Connected to Tor on %s:%d\n", LOCALHOST_IP, TORALIZE_PORT);
    close(sockfd);
    return 0;
}