#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "login.h"
#include "messagebuilder.h"

void logIn(int ssock) {
    char id[BUFSIZ / 2], password[BUFSIZ / 2], 
         buffer[BUFSIZ], response[BUFSIZ];
    printf("start log in process\n");

    while (1) {
        printf("ID : ");
        fgets(id, BUFSIZ, stdin);
        removeNewline(id);
        printf("PW : ");
        fgets(password, BUFSIZ, stdin);
        removeNewline(password);

        if (send(ssock, createLoginMessage(id, password), BUFSIZ, MSG_DONTWAIT) <= 0) {
            perror("send()");
            exit(1);
        }

        if (recv(ssock, response, BUFSIZ, 0) <= 0) {
            perror("recv()");
            exit(1);
        }

        printf("Received data : %s\n", response);

        break;
    }
}
