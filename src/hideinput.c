#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "authheader.h"

void disableEcho() {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag &= ~(ECHO | ECHONL);
    tty.c_lflag |= ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

void enableEcho() {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag |= (ECHO | ECHONL);  // 에코 및 개행 켜기
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

void getPassword(char *password, size_t len) {
    char c;
    size_t i = 0;

    disableEcho();

    while (i < len - 1) {
        c = getchar();

        if (c == '\n') {
            break;
        } else if (c == 127 || c == '\b') {  // 백스페이스 처리
            if (i > 0) {
                printf("\b \b");  // 화면에서 '*' 지우기
                i--;
            }
        } else {
            password[i++] = c;  // 입력된 문자 저장
            printf("*");  
        }
    }

    password[i] = '\0';
    enableEcho();

    printf("\n");
}
