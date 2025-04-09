//2. Write a program for a distance vector algorithm to find a suitable path for transmission.

#include <stdio.h>

struct node
{
    int dist[20];
    int from[20];
} rt[10];

int main()
{
    int n, d[20][20];

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    printf("Enter the distance matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &d[i][j]);
            rt[i].dist[j] = d[i][j];
            rt[i].from[j] = j;
        }

    int flag;
    do
    {
        flag = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++)
                    if (rt[i].dist[j] > d[i][k] + rt[k].dist[j])
                    {
                        rt[i].dist[j] = d[i][k] + rt[k].dist[j];
                        rt[i].from[j] = k;
                        flag = 1;
                    }
    } while (flag);

    for (int i = 0; i < n; i++)
    {
        printf("\nRouter information for router:%d:\nDestination\tNextHop\t\tDistance\n", i + 1);
        for (int j = 0; j < n; j++)
            printf("%d\t\t%d\t\t%d\n", j + 1, rt[i].from[j] + 1, rt[i].dist[j]);
    }
}


//Example
// Enter number of nodes: 4
// Enter the distance matrix:
// 0
// 3
// 5
// 99
// 3
// 0
// 99
// 1
// 5
// 4
// 0
// 2
// 99
// 1
// 2
// 0

// Router information for router:1:
// Destination     NextHop         Distance
// 1               1               0
// 2               2               3
// 3               3               5
// 4               2               4

// Router information for router:2:
// Destination     NextHop         Distance
// 1               1               3
// 2               2               0
// 3               4               3
// 4               4               1

// Router information for router:3:
// Destination     NextHop         Distance
// 1               1               5
// 2               4               3
// 3               3               0
// 4               4               2

// Router information for router:4:
// Destination     NextHop         Distance
// 1               2               4
// 2               2               1
// 3               3               2
// 4               4               0
