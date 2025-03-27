#include <stdio.h>

int main() 
{
    int d[4], h[7];

    printf("Data: "); 
    for (int i = 0; i < 4; i++) scanf("%1d", &d[i]);

    h[6] = d[0]; 
    h[5] = d[1]; 
    h[4] = d[2]; 
    h[2] = d[3];

    h[0] = h[2] ^ h[4] ^ h[6]; 
    h[1] = h[2] ^ h[5] ^ h[6];  
    h[3] = h[4] ^ h[5] ^ h[6];

    printf("Hamming: "); 
    for (int i = 6; i >= 0; i--) printf("%d", h[i]); 
    printf("\n");

    printf("Received: "); 
    for (int i = 6; i >= 0; i--) scanf("%1d", &h[i]);

    int e = (h[0] ^ h[2] ^ h[4] ^ h[6]) | ((h[1] ^ h[2] ^ h[5] ^ h[6]) << 1) | ((h[3] ^ h[4] ^ h[5] ^ h[6]) << 2); 

    if (e)
    {
        printf("Error at %d\n", e);
        h[e - 1] ^= 1;
    }

    printf("Code: "); 
    for (int i = 6; i >= 0; i--) printf("%d", h[i]); 
    printf("\n");

    return 0;
}



//Example
// Data: 1
// 0
// 1
// 1
// Hamming: 1010101
// Received: 1
// 0
// 1
// 1
// 1
// 1
// 1
// Error at 6
// Code: 1111111
