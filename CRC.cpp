#include <stdio.h>
#include <string.h>

void crc(char *msg, char *rem, char *gen) 
{
    int glen = strlen(gen);
    int mlen = strlen(msg) - glen + 1;
    
    strncpy(rem, msg, glen);
    for (int i = 0; i < mlen; i++) 
    {
        if (rem[0] == '1')
        {
            for (int j = 1; j < glen; j++)
            {
                rem[j] = (rem[j] == gen[j]) ? '0' : '1';
            }
        }
        
        memmove(rem, rem + 1, glen);
        rem[glen - 1] = msg[i + glen];
    }
    rem[glen] = '\0';
}

int main() 
{
    char data[128], gen[32], code[160], rem[32], recv[160];
    int pos, test;
    printf("No of bits: ");
    scanf("%d", &test);
    printf("Data: ");
    scanf("%s", data);
    printf("Gen: ");
    scanf("%s", gen);
    
    // Append zeros
    sprintf(code, "%s%0*d", data, strlen(gen)-1, 0);
    printf("Modified data: %s\n", code);
    
    // Calculate CRC
    crc(code, rem, gen);
    printf("Checksum: %s\n", rem);
    
    // Create final codeword
    strcpy(code + strlen(data), rem);
    printf("Final codeword: %s\n", code);
    
    // Error insertion
    printf("Error position: ");
    scanf("%d", &pos);
    strcpy(recv, code);
    recv[pos] = (recv[pos] == '0') ? '1' : '0';
    printf("Data with error: %s\n", recv);
    
    return 0;
}

//Example
// No of bits: 8
// Data: 11010011101100
// Gen: 1011
// Modified data: 11010011101100000
// Checksum: 100
// Final codeword: 11010011101100100
// Error position: 5
// Data with error: 11010111101100100
