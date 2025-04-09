//10. Write a program for congestion control using Leaky bucket algorithm.

#include <stdio.h>

int main()
{
    int n, time[50], size[50], bucket = 0, bsize, rate, t = 1;

    printf("Enter number of packets: ");
    scanf("%d", &n);
    printf("Enter packets in order of their arrival time: \n");
    for (int i = 0; i < n; i++)
    {
        printf("Enter time and size of packet %d: ", i + 1);
        scanf("%d %d", &time[i], &size[i]);
    }
    printf("Enter bucket size and output rate: ");
    scanf("%d %d", &bsize, &rate);
    
    int i = 0;
    while (t <= time[n - 1] || bucket > 0)
    {
        printf("\n At time %d", t);

        // Insert packet if its time has come
        if (i < n && time[i] == t)
        {
            if (bucket + size[i] <= bsize)
            {
                bucket += size[i];
                printf("\nInserted %d bytes", size[i]);
            }
            else
            {
                printf("\nTransferred %d bytes", size[i]);
            }
            i++;
        }
        // Send from bucket
        int send = (bucket < rate) ? bucket : rate;
        bucket -= send;
        printf("\nSent packet of %d bytes\nIn bucket: %d bytes", send, bucket);

        t++;
    }

    return 0;
}



// Example
// Enter number of packets: 3
// Enter packets in order of their arrival time: 
// Enter time and size of packet 1: 1 4
// Enter time and size of packet 2: 2 6
// Enter time and size of packet 3: 4 8
// Enter bucket size and output rate: 10 5
//  At time 1
// Inserted 4 bytes
// Sent packet of 4 bytes
// In bucket: 0 bytes
//  At time 2
// Inserted 6 bytes
// Sent packet of 5 bytes
// In bucket: 1 bytes
//  At time 3
// Sent packet of 1 bytes
// In bucket: 0 bytes
//  At time 4
// Inserted 8 bytes
// Sent packet of 5 bytes
// In bucket: 3 bytes
//  At time 5
// Sent packet of 3 bytes
// In bucket: 0 bytes



// Enter number of packets: 4
// Enter packets in order of their arrival time: 
// Enter time and size of packet 1: 1 6
// Enter time and size of packet 2: 2 7
// Enter time and size of packet 3: 3 5
// Enter time and size of packet 4: 4 4
// Enter bucket size and output rate: 10 4
//  At time 1
// Inserted 6 bytes
// Sent packet of 4 bytes
// In bucket: 2 bytes
//  At time 2
// Inserted 7 bytes
// Sent packet of 4 bytes
// In bucket: 5 bytes
//  At time 3
// Inserted 5 bytes
// Sent packet of 4 bytes
// In bucket: 6 bytes
//  At time 4
// Inserted 4 bytes
// Sent packet of 4 bytes
// In bucket: 6 bytes
//  At time 5
// Sent packet of 4 bytes
// In bucket: 2 bytes
//  At time 6
// Sent packet of 2 bytes
// In bucket: 0 bytes




// Enter number of packets: 3
// Enter packets in order of their arrival time: 
// Enter time and size of packet 1: 1 10
// Enter time and size of packet 2: 2 5
// Enter time and size of packet 3: 3 3
// Enter bucket size and output rate: 15 3
//  At time 1
// Inserted 10 bytes
// Sent packet of 3 bytes
// In bucket: 7 bytes
//  At time 2
// Inserted 5 bytes
// Sent packet of 3 bytes
// In bucket: 9 bytes
//  At time 3
// Inserted 3 bytes
// Sent packet of 3 bytes
// In bucket: 9 bytes
//  At time 4
// Sent packet of 3 bytes
// In bucket: 6 bytes
//  At time 5
// Sent packet of 3 bytes
// In bucket: 3 bytes
//  At time 6
// Sent packet of 3 bytes
// In bucket: 0 bytes
