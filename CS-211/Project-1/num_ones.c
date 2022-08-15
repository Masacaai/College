#include <stdio.h>
#include <stdlib.h>

int main() {
    int num, temp, ret;
    int arr[10];
    int result = 0;

    printf("Enter a non-negative integer: ");
    ret = scanf("%d", &num);
    if (ret == 0 || num < 0) {
        printf("INVALID INPUT");
        exit(0);
    }
    temp = num;
    for (int i = 0; temp > 0; i++) {
        arr[i] = temp % 2;
        if (arr[i] == 1) {
            result++;
        }
        temp /= 2;
    }
    printf("%d has %d ones in binary", num, result);
    return 0;
}