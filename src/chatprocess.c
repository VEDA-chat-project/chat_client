#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>


#include "chatprocess.h"
#include "messagebuilder.h"

void chatStart(int ssock, char* id) {
    int n;
    char msg[BUFSIZ];
    pid_t pid;

    pid = fork();
    if (pid == -1) {
        perror("fork()");
        exit(1);
    }

    if (pid == 0) { // child process : read messages from chat_server
        int bytes;

        while (1) {
            bytes = read(ssock, msg, BUFSIZ);
            if (bytes <= 0) {
                break;
            }
            msg[bytes] = '\0';
            printf("%s\n", msg);
        }

        exit(0);
    } else { // parent process : write messages to chat_server
        while (1) {
            fgets(msg, BUFSIZ, stdin);

            if (strncmp(msg, "exit", 4) == 0) { // exit chat room
                break;
            }

            msg[strcspn(msg, "\n")] = '\0';

            /* 
             * Build a message format "MESSAGE:id msg".
             * See messagebuilder.c code.
             */
            char* format = createChatMessage(id, msg); 

            send(ssock, format, strlen(format), 0);
            free(format);
        }
    
    }

}
