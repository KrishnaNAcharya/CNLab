#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct 
{ 
    int id; 
    char t[4]; 
} P;

int main() 
{
    char m[100];
    printf("Msg: ");
    fgets(m, sizeof(m), stdin);
    m[strcspn(m, "\n")] = 0;  

    int n = (strlen(m) + 2) / 3;
    P *p = (P *)malloc(n * sizeof(P));

    for (int i = 0; i < n; i++) 
    {
        p[i].id = i + 1;
        strncpy(p[i].t, m + i * 3, 3);
        p[i].t[3] = '\0'; 
    }

    printf("Packet No.  Data\n\n");
    for (int i = 0; i < n; i++)
    { 
        printf("%d:%s ", p[i].id, p[i].t);
        printf("\n");
    }

    srand(time(NULL));
    for (int i = n - 1; i > 0; i--) 
    {
        int j = rand() % (i + 1);
        P temp = p[i];
        p[i] = p[j];
        p[j] = temp;
    }

    printf("\nPackets Received: ");
    for (int i = 0; i < n; i++) 
        printf("%d ", p[i].id);

    printf("\nPackets in order: ");
    for (int i = 0; i < n; i++) 
        printf("%d ", i + 1);
    
    return 0;
}

//Example
// Msg: A computer network is a set of devices connected through links
// Packet No.  Data

// 1:A c
// 2:omp
// 3:ute
// 4:r n
// 5:etw
// 6:ork
// 7: is
// 8: a
// 9:set
// 10: of
// 11: de
// 12:vic
// 13:es
// 14:con
// 15:nec
// 16:ted
// 17: th
// 18:rou
// 19:gh
// 20:lin
// 21:ks

// Packets Received: 1 16 5 21 12 10 20 18 15 8 7 19 13 14 2 9 17 11 3 4 6
// Packets in order: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21
