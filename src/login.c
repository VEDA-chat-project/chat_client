#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "login.h"

void logIn(int ssock) {
    char id[BUFSIZ], password[BUFSIZ];
    printf("start log in process\n");

    while (1) {
        printf("ID : ");
        fgets(id, BUFSIZ, stdin);
        printf("PW : ");
        fgets(password, BUFSIZ, stdin);

        break;
    }
}
