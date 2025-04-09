//1. Write a program for error detecting code using CRC-CCITT (16-bits)

#include <stdio.h>
#include <string.h>

int main()
{
    char data[128], gen[32], code[160], rem[32], recv[160];
    int pos, i, j, e;

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

    printf("Enter 1 if there's an error needed to be transmitted, 0 otherwise: ");
    scanf("%d", &e);
    if (e == 1)
    {
        printf("Enter error position : ");
        scanf("%d", &pos);
        recv[pos-1] ^= 1; // Flip the bit using XOR
    }
    printf("Data with error: %s\n", recv);

    return 0;
}


//Example
//Enter Data and Generator: 1101011011 10011
//Modified Data padded with n-1 zero: 11010110110000
//CRC value: 1110
//Final data sent: 11010110111110
//Enter 1 if there's an error needed to be transmitted, 0 otherwise: 1
//Enter error position : 3
//Data recieved through transmission: 11110110111110

//Enter Data and Generator: 1101011011 10011
//Modified Data padded with n-1 zero: 11010110110000
//CRC value: 1110
//Final data sent: 11010110111110
//Enter 1 if there's an error needed to be transmitted, 0 otherwise: 0
//Data recieved through transmission: 11010110111110
