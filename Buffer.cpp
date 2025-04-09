//3. Write a program for frame sorting techniques used in buffers. 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Packet
{
    int id;
    char data[4];
};

int main()
{
    char msg[100];
    printf("Enter the message to be transmitted: ");
    fgets(msg, sizeof(msg), stdin);

    int len = strlen(msg);
    int n = (len + 2) / 3;
    struct Packet p[50];

    for (int i = 0; i < n; i++)
    {
        p[i].id = i + 1;
        strncpy(p[i].data, msg + i * 3, 3);
        p[i].data[3] = '\0';
    }

    printf("Packet No.  Data\n\n");
    for (int i = 0; i < n; i++)
        printf("%d:%s\n", p[i].id, p[i].data);

    // Shuffle
    srand(time(0));
    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        struct Packet temp = p[i];
        p[i] = p[j];
        p[j] = temp;
    }

    printf("\nPackets Received in following order: ");
    for (int i = 0; i < n; i++)
        printf("%d ", p[i].id);

    // Sort (bubble sort)
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (p[j].id > p[j + 1].id)
            {
                struct Packet temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }

    printf("\nPackets in order after sorting: ");
    for (int i = 0; i < n; i++)
        printf("%d ", p[i].id);

    printf("\n\nReassembled message after sorting:\n");
    for (int i = 0; i < n; i++)
        printf("%s", p[i].data);
    printf("\n");

    return 0;
}





//Example
// Enter the message to be transmitted: A computer network is a set of devices connected through links
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

// Packets Received in following order: 16 6 2 11 3 1 10 4 8 13 12 7 14 19 18 17 21 20 15 5 9
// Packets in order after sorting: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21

// Reassembled message after sorting:
// A computer network is a set of devices connected through links
