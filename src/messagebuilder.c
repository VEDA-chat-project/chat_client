#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "messagebuilder.h"

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
