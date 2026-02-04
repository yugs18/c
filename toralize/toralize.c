/* toralize.c */
#include "toralize.h"

// ./toralize.c <target_ip> <target_port>

int main(int argc, char *argv[]) {
    char *target_ip;
    int target_port;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <target_ip> <target_port>\n", argv[0]);
        return -1;
    }
    target_ip = argv[1];
    target_port = atoi(argv[2]);
}