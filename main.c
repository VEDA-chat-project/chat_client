#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define TCP_PORT 5100

int main(int argc, char **argv) {
    int ssock;
    struct sockaddr_in servaddr;
    char mesg[BUFSIZ];

    if (argc < 2) {
        printf("Usage : %s IP_ADRESS\n", argv[0]);
        exit(1);
    }

    if ((ssock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket()");
        exit(1);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;

    inet_pton(AF_INET, argv[1], &(servaddr.sin_addr.s_addr));
    servaddr.sin_port = htons(TCP_PORT);

    if (connect(ssock, (struct sockaddr*) &servaddr, sizeof(servaddr)) < 0) {
        perror("connect()");
        exit(1);
    }

    char cmd;
    do {
        printf("1. Log in\n");
        printf("2. Sign up\n");
        printf("3. exit\n");
        printf("select > ");
        scanf("%c", &cmd);
        getchar();
        switch (cmd) {
            case '1': // Log in
                break;
            case '2': // Sign up
                break;
            case '3': // exit
                exit(0);
            default:
                printf("You have selected wrong command.\n");
                break;
        }
    } while (cmd != '3');

    return 0;
}
