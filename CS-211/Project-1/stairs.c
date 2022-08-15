#include <stdio.h>
#include <stdlib.h>

int main() {
    int num, ret;

    printf("Enter number of stairs: ");
    ret = scanf("%i", &num);
    if (ret == 0 || num < 0) {
        printf("INVALID INPUT");
        exit(0);
    }
    printf("\n");

    // up
    printf("up:\n\n");
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num - i - 1; j++) {
            printf(" ");
        }
        for (int j = 0; j < i + 1; j++) {
            printf("X");
        }
        printf("\n");
    }

    // down
    printf("down:\n\n");
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < i + 1; j++) {
            printf("X");
        }
        printf("\n");
    }

    //up-down
    printf("up-down:\n\n");
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < (((2*(num - 1))+1) - ((2*i)+1)) / 2; ++j) {
            printf(" ");
        }
        for(int j = 0; j < (2*i) + 1; ++j) {
            printf("X");
        }
        printf("\n");
    }

    printf("\n");

    return 0;
}