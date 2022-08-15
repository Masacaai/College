#include <stdio.h>
#include <stdlib.h>

int main() {
    int num[3];
    int ret, max, min, mid;

    // Insert values into array
    for (int i = 0; i < 3; ++i) {
        printf("Enter an integer: ");
        ret = scanf("%i", &num[i]);
        if (ret == 0) {
            printf("INVALID INPUT");
            exit(0);
        }
    }

    // Bubble Sort
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2-i; ++j) {
            if (num[j] > num[j+1]) {
                int temp = num[j];
                num[j] = num[j+1];
                num[j+1] = temp;
            }
        }
    }

    printf("median: %d", num[1]);

    return 0;
}