#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int areCoprime(int a, int b) {
    return gcd(a, b) == 1;
}

void findAllowedValuesOfA() {
    printf("Allowed values of 'a' for the affine Caesar cipher are:\n");
    for (int a = 1; a < 26; a++) {
        if (areCoprime(a, 26)) {
            printf("%d ", a);
        }
    }
    printf("\n");
}

int main() {
    findAllowedValuesOfA();
    return 0;
}
