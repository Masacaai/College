#include <stdio.h>
#include <stdlib.h>

int main() {
    int numA, numB, numC, numD, max, ret;

    printf("A: ");
    ret = scanf("%d", &numA);
    if (ret == 0 || numA < 0) {
        printf("INVALID INPUT");
        exit(0);
    }

    printf("B: ");
    ret = scanf("%d", &numB);
    if (ret == 0 || numB < 0) {
        printf("INVALID INPUT");
        exit(0);
    }
    
    printf("C: ");
    ret = scanf("%d", &numC);
    if (ret == 0 || numC < 0) {
        printf("INVALID INPUT");
        exit(0);
    }
    
    printf("D: ");
    ret = scanf("%d", &numD);
    if (ret == 0 || numD < 0) {
        printf("INVALID INPUT");
        exit(0);
    }

    if (numA >= numB && numA >= numC && numA >= numD) {
        max = numA;
    }

    if (numB >= numA && numB >= numC && numB >= numD) {
        max = numB;
    }

    if (numC >= numA && numC >= numB && numC >= numD) {
        max = numC;
    }

    if (numD >= numA && numD >= numB && numD >= numC) {
        max = numD;
    }

    printf("\n");
    for (int i = max; i > 0; --i) {
        if (i <= numA) {
            printf(" X ");
        }
        else {
            printf("   ");
        }

        if (i <= numB) {
            printf("X ");
        }
        else {
            printf("  ");
        }

        if (i <= numC) {
            printf("X ");
        }
        else {
            printf("  ");
        }

        if (i <= numD) {
            printf("X");
        }
        else {
            printf(" ");
        }
        printf("\n");
    }
    printf("---------\n");
    printf(" A B C D");
    return 0;
}