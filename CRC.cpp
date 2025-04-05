#include <stdio.h>
#include <string.h>

int main() 
{
    char data[128], gen[32], code[160], rem[32], recv[160];
    int pos, test;
    
    printf("Enter No of bits, Data, Gen: ");
    scanf("%d %s %s", &test, data, gen);    
    
    sprintf(code, "%s%0*d", data, strlen(gen) - 1, 0);
    printf("Modified data: %s\n", code);

    int glen = strlen(gen);
    int mlen = strlen(code) - glen + 1;
    
    strncpy(rem, code, glen);
    for (int i = 0; i < mlen; i++) 
    {
        if (rem[0] == '1')
        {
            for (int j = 1; j < glen; j++)
                rem[j] = (rem[j] == gen[j]) ? '0' : '1';
        }
        
        memmove(rem, rem + 1, glen);
        rem[glen - 1] = code[i + glen];
    }
    rem[glen] = '\0';
    strcpy(code + strlen(data), rem);
    strcpy(recv, code);
    
    printf("Checksum: %s\n", rem);
    printf("Final codeword: %s\n", code);

    printf("Error position: ");
    scanf("%d", &pos);
    
    recv[pos] = (recv[pos] == '0') ? '1' : '0';
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
