#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

int main() 
{
    printf("Server Running on port 60000...\n");

    int s = socket(AF_INET, SOCK_STREAM, 0), c;
    struct sockaddr_in a = {AF_INET, htons(60000)};
    bind(s, (sockaddr*)&a, sizeof(a));
    listen(s, 1);

    c = accept(s, 0, 0);
    printf("Client connected\n");
    char b[99];

    while (recv(c, b, sizeof(b), 0), strcmp(b, "exit")) 
    {
     	printf("Client requested file: %s\n", b);
        FILE* f = fopen(b, "r");
        if (f) 
        {
            while (fgets(b, sizeof(b), f)) send(c, b, strlen(b), 0);
            fclose(f);
        } 
        else send(c, "404 file not found\n", 3, 0);
    }
    
    close(c);
}
