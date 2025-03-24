#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

int main() 
{
    printf("Enter File name: \n");

    int s = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in a = {AF_INET, htons(65535)};
    connect(s, (sockaddr*)&a, sizeof(a));

    char f[9], b[99];

    while (printf(">"), scanf("%s", f), strcmp(f, "q")) 
    {
        send(s, f, strlen(f) + 1, 0);
        recv(s, b, sizeof(b), 0);
        printf("%s", b);
    }

    send(s, "q", 2, 0);
    close(s);
}
