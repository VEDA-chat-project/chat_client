#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "authheader.h"
#include "messagebuilder.h"

void signUp(int ssock) {
    char id[50], password[50], 
         buffer[BUFSIZ], response[BUFSIZ];

    printf("start sign up process\n");

    while (1) {
        printf("ID : ");
        fgets(id, 50, stdin);
        removeNewline(id);
        printf("PW : ");
        fgets(password, 50, stdin);
        removeNewline(password);

        if (send(ssock, createSignupMessage(id, password), BUFSIZ, MSG_DONTWAIT) <= 0) {
            perror("send()");
            exit(1);
        }

        if (recv(ssock, response, BUFSIZ, 0) <= 0) {
            perror("recv()");
            exit(1);
        }

        printf("%s\n", response);

        break;
    }

}
