#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

int main() 
{
    printf("Server Running......\n");

    int s = socket(AF_INET, SOCK_STREAM, 0), c;
    struct sockaddr_in a = {AF_INET, htons(65535)};
    bind(s, (sockaddr*)&a, sizeof(a));
    listen(s, 1);

    c = accept(s, 0, 0);
    char b[99];

    while (recv(c, b, sizeof(b), 0), strcmp(b, "q")) 
    {
        FILE* f = fopen(b, "r");
        if (f) 
        {
            while (fgets(b, sizeof(b), f)) send(c, b, strlen(b), 0);
            fclose(f);
        } 
        else send(c, "404", 3, 0);
    }
    
    close(c);
}
