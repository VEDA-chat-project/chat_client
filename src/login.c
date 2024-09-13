#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "authheader.h"
#include "messagebuilder.h"
#include "chatprocess.h"

void logIn(int ssock) {
    char id[50], password[50], buffer[BUFSIZ];
    int response;

    while (1) {
        printf("Pleas enter your ID/PW.\n");
        printf("ID : ");
        fgets(id, 50, stdin);
        removeNewline(id);
        printf("PW : ");
        fgets(password, 50, stdin);
        removeNewline(password);

        if (send(ssock, createLoginMessage(id, password), BUFSIZ, MSG_DONTWAIT) <= 0) {
            perror("send()");
            exit(1);
        }

        if (recv(ssock, &response, sizeof(int), 0) <= 0) {
            perror("recv()");
            exit(1);
        }

        if (response == 1) { // log in success
            printf("Log in success!\n");
            chatStart(ssock, id);
            break;
        } else {
            printf("Invalid ID/PW.\n");
            char c;
            do {
                printf("(r)etry | (q)uit > ");
                scanf("%c", &c);
                getchar();
            } while(c != 'r' && c != 'q');
            
            if (c == 'q') break;
        }

    }
}
