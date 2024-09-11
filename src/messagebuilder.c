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

char* createMessage(const char* prefix, const char* part1, const char* part2) {
    size_t message_length = strlen(prefix) + strlen(part1) + 1;  // 프리픽스 + part1 + 스페이스 또는 NULL
    if (part2 != NULL) {
        message_length += strlen(part2) + 1;  // part2가 있으면 스페이스 포함
    }

    char* message = (char*)malloc(message_length);
    if (message == NULL) {
        perror("Unable to allocate memory");
        return NULL;
    }

    if (part2 != NULL) {
        snprintf(message, message_length, "%s%s %s", prefix, part1, part2);
    } else {
        snprintf(message, message_length, "%s%s", prefix, part1);
    }

    return message;
}

char* createLoginMessage(const char* id, const char* password) {
    return createMessage("LOGIN:", id, password);
}

char* createSignupMessage(const char* id, const char* password) {
    return createMessage("SIGNUP:", id, password);
}

char* createChatMessage(const char* chat) {
    return createMessage("MESSAGE:", chat, NULL);
}
