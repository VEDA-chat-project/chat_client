#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "authheader.h"
#include "messagebuilder.h"
#include "chatprocess.h"

void logIn(int ssock) {
    char id[50], password[50]; 
    int response;

    while (1) { // input ID/PW
        printf("------------------------------\n");
        printf("Pleas enter your ID/PW.\n");
        printf("ID : ");
        fgets(id, 50, stdin);
        removeNewline(id);
        printf("PW : ");
        getPassword(password, 50);
        //fgets(password, 50, stdin);
        //removeNewline(password);

        /*
         * Build a message format "LOGIN:id password"
         * See messagebuilder.c code.
        */
        if (send(ssock, createLoginMessage(id, password), BUFSIZ, MSG_DONTWAIT) <= 0) {
            perror("send()");
            exit(1);
        }

        if (recv(ssock, &response, sizeof(int), 0) <= 0) {
            perror("recv()");
            exit(1);
        }

        if (response == 1) { // Log in success
            printf("Log in success!\n");
            chatStart(ssock, id); // go to 'chatprocess.c' code
            break;
        } else { // Log in failed
            printf("Invalid ID/PW.\n");
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
