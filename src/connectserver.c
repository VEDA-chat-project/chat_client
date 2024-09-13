#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "connectserver.h"

#define TCP_PORT 5100

int connectToServer(const char* ip) {
    int ssock;
    struct sockaddr_in servaddr;

    if ((ssock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket()");
        exit(1);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &(servaddr.sin_addr.s_addr));
    servaddr.sin_port = htons(TCP_PORT);

    if (connect(ssock, (struct sockaddr*) &servaddr, sizeof(servaddr)) < 0) {
        perror("connect()");
        close(ssock); // 연결 실패 시 소켓 닫기
        exit(1);
    }

    return ssock;
}
