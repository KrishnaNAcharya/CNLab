//1. Write a program for error detecting code using CRC-CCITT (16-bits)
#include <stdio.h>
#include <string.h>

int main()
{
    char data[128], gen[32], code[160], rem[32], recv[160];
    int pos, i, j;

    printf("Enter Data and Generator: ");
    scanf("%s %s", data, gen);

    int dlen = strlen(data), glen = strlen(gen);
    sprintf(code, "%s%0*d", data, glen - 1, 0);
    printf("Modified Data: %s\n", code);

    strncpy(rem, code, glen);
    for (i = 0; i <= strlen(code) - glen; i++)
    {
        if (rem[0] == '1')
            for (j = 1; j < glen; j++)
                rem[j] = (rem[j] == gen[j]) ? '0' : '1';

        memmove(rem, rem + 1, glen - 1);
        rem[glen - 1] = code[i + glen];
    }
    rem[glen - 1] = '\0';

    strcpy(code + dlen, rem);
    strcpy(recv, code);

    printf("Checksum: %s\n", rem);
    printf("Codeword: %s\n", code);

    printf("Enter error position (0-based): ");
    scanf("%d", &pos);
    recv[pos] ^= 1; // Flip the bit using XOR
    printf("Data with error: %s\n", recv);

    return 0;
}



//Example
// Enter No of bits, Data, Gen: 8 11010011101100 1011
// Modified data: 11010011101100000
// Checksum: 100
// Final codeword: 11010011101100100
// Error position: 5
// Data with error: 11010111101100100
