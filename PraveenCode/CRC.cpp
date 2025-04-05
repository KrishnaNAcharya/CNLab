#include <stdio.h>
#include <string.h>

#define MAX_LEN 128

char t[MAX_LEN], cs[MAX_LEN], cd[MAX_LEN];
char g[MAX_LEN];
int a, e, c, b, g_len;

void xor_operation() {
    for (c = 1; c < g_len; c++) {
        cs[c] = (cs[c] == g[c]) ? '0' : '1';
    }
}

void crc() {
    for (e = 0; e < g_len; e++) {
        cs[e] = t[e];
    }

    do {
        if (cs[0] == '1') {
            xor_operation();
        }

        for (c = 0; c < g_len - 1; c++) {
            cs[c] = cs[c + 1];
        }
        cs[c] = t[e++];
    } while (e <= a + g_len - 1);
}

int main() {
    printf("Enter the number of data bits: ");
    int data_len;
    scanf("%d", &data_len);
   
    printf("\nEnter the data bits: ");
    scanf("%s", t);
   
    printf("\nEnter the generator polynomial: ");
    scanf("%s", g);
   
    g_len = strlen(g);
   
    char original_data[MAX_LEN];
    strcpy(original_data, t);

    a = strlen(t);
    for (e = a; e < a + g_len - 1; e++) {
        t[e] = '0';
    }

    printf("\nModified t[u] (data with appended zeros) is: %s", t);

    crc();

    printf("\nChecksum is: %s", cs);

    for (e = a; e < a + g_len - 1; e++) {
        t[e] = cs[e - a];
    }

    printf("\nFinal codeword (transmitted data) is: %s", t);

    printf("\n\nTest error detection (1 for yes, 0 for no)? ");
    scanf("%d", &b);

    if (b == 1) {
        int pos;
        printf("Enter position where error is to be inserted: ");
        scanf("%d", &pos);

        if (pos >= 0 && pos < a + g_len - 1) {
            char data_with_error[MAX_LEN];
            strcpy(data_with_error, t);

            t[pos] = (t[pos] == '0') ? '1' : '0';  
            printf("\nData with error (modified data): %s\n", t);

            crc();

            int error = 0;
            for (c = 0; c < g_len - 1; c++) {
                if (cs[c] != '0') {
                    error = 1;
                    break;
                }
            }

            if (error) {
                printf("Error detected in the received data.\n");
            } else {
                printf("No error detected in the received data.\n");
            }

            printf("\nOriginal transmitted data: %s", original_data);
            printf("\nReceived data with error: %s", t);
        } else {
            printf("Invalid position! Error insertion failed.\n");
        }
    } else {
        printf("\nNo error detection simulated. Exiting.\n");
    }

    return 0;
}