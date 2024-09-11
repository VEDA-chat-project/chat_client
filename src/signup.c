#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "signup.h"

void signUp(int ssock) {
    char id[BUFSIZ], password[BUFSIZ];
    printf("start sign up process\n");

    while (1) {
        printf("ID : ");
        fgets(id, BUFSIZ, stdin);
        printf("PW : ");
        fgets(password, BUFSIZ, stdin);

        break;
    }

}
