/* toralize.c */
#include "toralize.h"

/*
1. Turn the client into a lib (shared library) .SO
2. Turn main()_ into our own connect()
3. Replace regular connect()
4. Grab the ip and port from original connect()
5. Doing what we do now
*/

// ./toralize.c <target_ip> <target_port>

Req *create_request(const char *target_ip, int target_port) {
    Req *req = malloc(request_size);

    req->vn = 4; // SOCKS4
    req->cd = 1; // CONNECT
    req->dstport = htons(target_port);
    req->dstip = inet_addr(target_ip);
    strncpy(req->userid, USERNAME, sizeof(req->userid) - 1);

    return req;
}

int main(int argc, char *argv[]) {
    char *target_ip;
    int target_port, sockfd;

    struct sockaddr_in sock;
    Req *req;

    char buffer[response_size];
    Res *res;

    int success;
    char temp[512];

    // predicate/property -> A funcction or operation that returns a boolean value.

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

    printf("Connected to Tor on %s:%d\n", LOCALHOST_IP, TORALIZE_PORT);

    req = create_request(target_ip, target_port);
    write(sockfd, req, request_size);

    memset(buffer, 0, response_size);
    if (read(sockfd, buffer, response_size) < 1) {
        perror("Failed to read response from Tor");
        free(req);
        close(sockfd);
        return -1;
    }

    res = (Res *)buffer;
    success = (res->cd == 90); // 90 means request granted
    if (!success) {
        fprintf(stderr, "Tor failed to connect to target %s:%d."
                "Error code %d\n", target_ip, target_port, res->cd);
        close(sockfd);
        free(req);
        return -1;
    }

    printf("Tor successfully connected to target %s:%d\n", target_ip, target_port);

    memset(temp, 0, sizeof(temp));
    snprintf(temp, sizeof(temp) - 1, 
                "HEAD / HTTP/1.0\r\n" 
                "Host: www.example.com\r\n" 
                "\r\n");

    write(sockfd, temp, strlen(temp));
    memset(temp, 0, sizeof(temp));
    if (read(sockfd, temp, sizeof(temp) - 1) < 1) {
        perror("Failed to read response from target");
        free(req);
        close(sockfd);
        return -1;
    }

    printf("Response from target: '%s'\n", temp);

    free(req);
    close(sockfd);
    return 0;
}