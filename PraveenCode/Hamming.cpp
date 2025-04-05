#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define FSize 3

typedef struct packet {
    int SeqNum;
    char Data[FSize + 1];
} packet;

struct packet *readdata, *transdata;

int divide(char *msg) {
    int msglen, NoOfPacket, i, j;
    msglen = strlen(msg);
    NoOfPacket = msglen / FSize;
    if ((msglen % FSize) != 0)
        NoOfPacket++;

    readdata = (struct packet *)malloc(sizeof(packet) * NoOfPacket);
    if (readdata == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    for (i = 0; i < NoOfPacket; i++) {
        readdata[i].SeqNum = i + 1;
        for (j = 0; (j < FSize) && (*msg != '\0'); j++, msg++)
            readdata[i].Data[j] = *msg;
        readdata[i].Data[j] = '\0';
    }

    printf("\nThe Message has been divided as follows\n");
    printf("\nPacket No.  Data\n\n");
    for (i = 0; i < NoOfPacket; i++)
        printf(" %2d  %s\n", readdata[i].SeqNum, readdata[i].Data);

    return NoOfPacket;
}

void shuffle(int NoOfPacket) {
    int *Status;
    int i, trans;
    srand(time(NULL));

    Status = (int *)calloc(NoOfPacket, sizeof(int));
    if (Status == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    transdata = (struct packet *)malloc(sizeof(packet) * NoOfPacket);
    if (transdata == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    for (i = 0; i < NoOfPacket;) {
        trans = rand() % NoOfPacket;
        if (Status[trans] != 1) {
            transdata[i].SeqNum = readdata[trans].SeqNum;
            strcpy(transdata[i].Data, readdata[trans].Data);
            i++;
            Status[trans] = 1;
        }
    }

    free(Status);
}

void sortframes(int NoOfPacket) {
    packet temp;
    int i, j;
    for (i = 0; i < NoOfPacket - 1; i++) {
        for (j = 0; j < NoOfPacket - i - 1; j++) {
            if (transdata[j].SeqNum > transdata[j + 1].SeqNum) {
                temp = transdata[j];
                transdata[j] = transdata[j + 1];
                transdata[j + 1] = temp;
            }
        }
    }
}

void receive(int NoOfPacket) {
    int i;
    printf("\nPackets received in the following order:\n");
    for (i = 0; i < NoOfPacket; i++)
        printf("%4d", transdata[i].SeqNum);

    sortframes(NoOfPacket);

    printf("\n\nPackets in order after sorting:\n");
    for (i = 0; i < NoOfPacket; i++)
        printf("%4d", transdata[i].SeqNum);

    printf("\n\nMessage received is:\n");
    for (i = 0; i < NoOfPacket; i++)
        printf("%s", transdata[i].Data);
    printf("\n");
}

int main() {
    char *msg;
    int NoOfPacket;

    msg = (char *)malloc(100 * sizeof(char));
    if (msg == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("\nEnter the message to be transmitted:\n");
    fgets(msg, 100, stdin);
    msg[strcspn(msg, "\n")] = 0; // Remove trailing newline

    NoOfPacket = divide(msg);
    shuffle(NoOfPacket);
    receive(NoOfPacket);

    free(readdata);
    free(transdata);
    free(msg);

    return 0;
}