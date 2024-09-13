#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "connectserver.h"
#include "authheader.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage : %s IP_ADRESS\n", argv[0]);
        exit(1);
    }

    char cmd;
    do { // main menu
        printf("------------------------------\n");
        printf("Please enter menu number.\n");
        printf("(1) Log in\n");
        printf("(2) Sign up\n");
        printf("(3) exit\n");
        printf("select > ");
        scanf("%c", &cmd);
        getchar();
        int ssock;
        switch (cmd) {
            case '1':
                ssock = connectToServer(argv[1]);
                logIn(ssock); // go to 'login.c' code
                close(ssock);
                break;
            case '2':
                ssock = connectToServer(argv[1]);
                signUp(ssock); // go to 'signup.c' code
                close(ssock);
                break;
            case '3': 
                exit(0);
            default:
                printf("You have selected wrong command.\n");
                break;
        }
    } while (cmd != '3');

    return 0;
}
