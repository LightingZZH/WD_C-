#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define ERR_EXIT(m) \
    do{ \
        perror(m);\
        exit(EXIT_FAILURE); \
    }while(0)

void do_service(int sockfd)
{
    char recvbuf[1024] = {0};
    char sendbuf[1024] = {0};
    while(1)
    {
        fgets(sendbuf, sizeof(sendbuf), stdin);
        write(sockfd, sendbuf, strlen(sendbuf));

        int ret = read(sockfd, recvbuf, sizeof(recvbuf));
        if(ret == -1){
            if(errno == EINTR)
                continue;
            ERR_EXIT("read");
        }else if(ret == 0){
            printf("server closed!\n");
            close(sockfd);
            exit(EXIT_SUCCESS);
        }
        printf("receive msg : %s\n",recvbuf);

        memset(recvbuf, 0, sizeof(recvbuf));
        memset(sendbuf, 0, sizeof(sendbuf));
    }
}

int main()
{
    int peerfd = socket(AF_INET, SOCK_STREAM, 0);
    if(peerfd == -1)
        ERR_EXIT("socket");
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("192.168.3.155");
    addr.sin_port = htons(2000);
    socklen_t len = sizeof(addr);
    if(connect(peerfd, (struct sockaddr*)&addr, len)==-1)
        ERR_EXIT("connect");

    char buf[1024];
    memset(buf, 0, sizeof(buf));
    read(peerfd, buf, sizeof(buf));
    printf("%s\n",buf);

    do_service(peerfd);
    return 0;
}

