#include <stdio.h>
#include <string.h>

#define MAX_SIZE 200

void performBitStuffing(const char *input, char *output) {
    int i = 0, j = 0;
    int consecutive_ones = 0;

    strcpy(output, "01111110");
    j = 8;

    while (input[i] != '\0') {
        output[j++] = input[i];

        if (input[i] == '1') {
            consecutive_ones++;
            
            if (consecutive_ones == 5) {
                output[j++] = '0';
                consecutive_ones = 0; 
            }
        } else {
            consecutive_ones = 0; 
        }
        i++;
    }

    strcpy(&output[j], "01111110");
}

int main() {
    char data[MAX_SIZE];
    char framed_data[MAX_SIZE * 2] = "";

    printf("Enter raw binary data stream (0s and 1s): ");
    if (scanf("%199s", data) != 1) return 1;

    performBitStuffing(data, framed_data);

    printf("Original Data: %s\n", data);
    printf("Framed Data:   %s\n", framed_data);

    return 0;
}