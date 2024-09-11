#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "login.h"

void removeNewline(char* str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

char* createLoginMessage(const char* id, const char* password) {
    const char* prefix = "LOGIN:";
    size_t message_length = strlen(prefix) + strlen(id) + 1 + strlen(password) + 1; // 1 for space, 1 for '\0'
    
    char* message = (char*)malloc(message_length);
    if (message == NULL) {
        perror("Unable to allocate memory");
        return NULL;
    }

    snprintf(message, message_length, "%s%s %s", prefix, id, password);

    return message;
}

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
