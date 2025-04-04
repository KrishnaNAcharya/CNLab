#include <stdio.h>

int main() 
{
    int n, time[50], size[50], bucket = 0, bsize, rate, t = 1, i = 0;

    printf("Packets: ");
    scanf("%d", &n);
    
    for (; i < n; i++) 
    {
        printf("Time & Size: ");
        scanf("%d %d", &time[i], &size[i]);
    }

    printf("Bucket size & Out rate: ");
    scanf("%d %d", &bsize, &rate);

    i = 0;

    while (t <= time[n - 1] || bucket > 0) 
    {
        printf("\nTime %d", t);

        if (time[i] == t) 
        {
            if (bucket + size[i] <= bsize) 
            {
                bucket += size[i];
                printf("\nInserted %d bytes", size[i]);
            } 
            else 
            {
                printf("\nDropped %d bytes", size[i]);
            }
            i++;
        }

        int send = (bucket < rate) ? bucket : rate;
        bucket -= send;
        printf("\nSent %d bytes\nIn bucket: %d", send, bucket);

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
