#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

int main() 
{
    printf("Connected to server.\n\n");

    int s = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in a = {AF_INET, htons(60000)};
    connect(s, (sockaddr*)&a, sizeof(a));

    char f[9], b[99];

    while (printf("\n Enter filename (or type 'exit' to quit):\n"), scanf("%s", f), strcmp(f, "exit")) 
    {
        send(s, f, strlen(f) + 1, 0);
        printf("\nServer Response:\n");
        recv(s, b, sizeof(b), 0);
        printf("%s", b);
    }

    send(s, "exit", 2, 0);
    close(s);
}
