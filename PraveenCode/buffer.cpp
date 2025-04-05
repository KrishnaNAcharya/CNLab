#include <stdio.h>

void generateHammingCode(int data[4], int hammingCode[7]) 
{
    hammingCode[6] = data[0]; // D4
    hammingCode[5] = data[1]; // D3
    hammingCode[4] = data[2]; // D2
    hammingCode[2] = data[3]; // D1

    hammingCode[0] = hammingCode[2] ^ hammingCode[4] ^ hammingCode[6]; // P1
    hammingCode[1] = hammingCode[2] ^ hammingCode[5] ^ hammingCode[6]; // P2
    hammingCode[3] = hammingCode[4] ^ hammingCode[5] ^ hammingCode[6]; // P3
}

void detectAndCorrectError(int receivedCode[7]) 
{
    int p1, p2, p3, errorPosition = 0;

    p1 = receivedCode[0] ^ receivedCode[2] ^ receivedCode[4] ^ receivedCode[6];
    p2 = receivedCode[1] ^ receivedCode[2] ^ receivedCode[5] ^ receivedCode[6];
    p3 = receivedCode[3] ^ receivedCode[4] ^ receivedCode[5] ^ receivedCode[6];

    errorPosition = (p3 << 2) | (p2 << 1) | (p1 << 0);

    if (errorPosition != 0) 
    {
        printf("Error detected at position %d\n", errorPosition);
        receivedCode[errorPosition - 1] ^= 1; // Flip the erroneous bit
        printf("Error corrected successfully!\n");
    } 
    else 
    {
        printf("No errors detected.\n");
    }

    printf("Corrected Hamming Code: ");
    for (int i = 6; i >= 0; i--) 
    {
        printf("%d", receivedCode[i]);
    }
    printf("\n");
}

int main() 
{
    int data[4], hammingCode[7], receivedCode[7];

    printf("Enter 4-bit data (space-separated): ");
    for (int i = 0; i < 4; i++) 
    {
        scanf("%d", &data[i]);
    }

    generateHammingCode(data, hammingCode);

    printf("Generated Hamming Code: ");
    for (int i = 6; i >= 0; i--) 
    {
        printf("%d", hammingCode[i]);
    }
    printf("\n");

    printf("Enter received 7-bit Hamming Code (space-separated): ");
    for (int i = 6; i >= 0; i--) 
    {
        scanf("%d", &receivedCode[i]);
    }

    detectAndCorrectError(receivedCode);

    return 0;
}
