#include <stdio.h>

struct packet {
    int time;
    int size;
} p[50];

int main() {
    int i, n, m, k = 0;
    int bsize, bfilled, outrate;

    printf("Enter the number of packets: ");
    scanf("%d", &n);

    printf("Enter packets in the order of their arrival time\n");
    for (i = 0; i < n; i++) {
        printf("Enter the time and size: ");
        scanf("%d %d", &p[i].time, &p[i].size);
    }

    printf("Enter the bucket size: ");
    scanf("%d", &bsize);

    printf("Enter the output rate: ");
    scanf("%d", &outrate);

    m = p[n - 1].time; // Stopping condition
    i = 1;             // Simulation time tracking
    k = 0;             // Current packet being processed
    bfilled = 0;       // Initial buffer filled

    while (i <= m || bfilled != 0) { // Until the last packet arrives and all data is transmitted
        printf("\n\nAt time %d", i);

        if (p[k].time == i) { // Insert Packet into Bucket
            if (bsize >= bfilled + p[k].size) { // If space is available
                bfilled = bfilled + p[k].size;
                printf("\n%d byte packet is inserted", p[k].size);
                k++;
            } else { // If bucket overflows
                printf("\n%d byte packet is discarded", p[k].size);
                k++;
            }
        }

        if (bfilled == 0) {
            printf("\nNo packets to transmit");
        } else if (bfilled >= outrate) {
            bfilled = bfilled - outrate;
            printf("\n%d bytes transferred", outrate);
        } else {
            printf("\n%d bytes transferred", bfilled);
            bfilled = 0;
        }

        printf("\nPackets in the bucket: %d byte(s)", bfilled);
        i++;
    }

    return 0;
}
