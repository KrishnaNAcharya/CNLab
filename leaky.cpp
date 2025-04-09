//6. Write a program for congestion control using Leaky bucket algorithm.

#include <stdio.h>

int main() 
{
    int n, time[50], size[50],bucket = 0, bsize, rate;

    
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

    int t = 1, i = 0;
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
        printf("\nSent packet of %d bytes\nIn bucket: %d", send, bucket);

        t++;
    }

    return 0;
}



// Example
// Packets: 4
// Time & Size: 1 5
// Time & Size: 2 6
// Time & Size: 3 8
// Time & Size: 4 6
// Bucket size & Out rate: 12 2

// Time 1
// Inserted 5 bytes
// Sent 2 bytes
// In bucket: 3
// Time 2
// Inserted 6 bytes
// Sent 2 bytes
// In bucket: 7
// Time 3
// Dropped 8 bytes
// Sent 2 bytes
// In bucket: 5
// Time 4
// Inserted 6 bytes
// Sent 2 bytes
// In bucket: 9
// Time 5
// Sent 2 bytes
// In bucket: 7
// Time 6
// Sent 2 bytes
// In bucket: 5
// Time 7
// Sent 2 bytes
// In bucket: 3
// Time 8
// Sent 2 bytes
// In bucket: 1
// Time 9
// Sent 1 bytes
// In bucket: 0
