/* srv.c */
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PORT 8181

int main() {
    int s, c;
    socklen_t addrlen;
    struct sockaddr_in srv, cli;
    char buf[512];
    char *data;

    addrlen = 0;
    memset(&srv, 0, sizeof(srv));
    memset(&cli, 0, sizeof(cli));

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        printf("Socket creation failed\n");
        return -1;
    }

    srv.sin_family = AF_INET;
    srv.sin_addr.s_addr = 0;
    srv.sin_port = htons(PORT);

    if (bind(s, (struct sockaddr *)&srv, sizeof(srv)) < 0) {
        printf("Bind failed\n");
        close(s);
        return -1;
    }

    if (listen(s, 5) < 0) {
        printf("Listen failed\n");
        close(s);
        return -1;
    }

    c = accept(s, (struct sockaddr *)&srv , &addrlen);
    if (c < 0) {
        printf("Accept failed\n");
        close(s);
        return -1;
    }

    printf("Connection accepted\n");
    read(c, buf, 511);
    data = "http v1.1\n";
    write(c, data, strlen(data));

    close(c);
    close(s);
    return 0;
}