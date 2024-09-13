#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "authheader.h"
#include "messagebuilder.h"

void signUp(int ssock) {
    char id[50], password[50];
    int response;

    while (1) { // input ID/PW
        printf("------------------------------\n");
        printf("ID : ");
        fgets(id, 50, stdin);
        removeNewline(id);
        printf("PW : ");
        fgets(password, 50, stdin);
        removeNewline(password);

        /*
         * Build a message format "SIGNUP:id password"
         * See messagebuilder.c code.
        */
        if (send(ssock, createSignupMessage(id, password), BUFSIZ, MSG_DONTWAIT) <= 0) {
            perror("send()");
            exit(1);
        }

        if (recv(ssock, &response, sizeof(int), 0) <= 0) {
            perror("recv()");
            exit(1);
        }

        if (response == 1) { // Sign up success
            printf("Sign up success!\n");
            break;
        } else { // Sign up failed
            printf("This ID is already in use.\n");
            char c;
            do {
                printf("(r)etry | (e)xit > ");
                scanf("%c", &c);
                getchar();
            } while(c != 'r' && c != 'e');

            if (c == 'e') break;
        }
    }

}
