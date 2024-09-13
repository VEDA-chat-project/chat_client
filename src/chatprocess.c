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

    if (pid == 0) { // child process
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
    } else { // parent process
        while (1) {
            fgets(msg, BUFSIZ, stdin);

            if (strncmp(msg, "exit", 4) == 0) {
                break;
            }

            msg[strcspn(msg, "\n")] = '\0';
            char* form = createChatMessage(id, msg);

            send(ssock, form, strlen(form), 0);
            free(form);
        }
    
    }

}
