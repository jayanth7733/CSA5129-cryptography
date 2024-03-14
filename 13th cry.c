#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 2

int determinant(int key[SIZE][SIZE]) {
    return (key[0][0] * key[1][1]) - (key[0][1] * key[1][0]);
}

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1;
}

void decrypt(int ciphertext[SIZE], int key[SIZE][SIZE]) {
    int det = determinant(key);
    int invDet = modInverse(det, 26);

    int inverseKey[SIZE][SIZE];
    inverseKey[0][0] = key[1][1];
    inverseKey[0][1] = -key[0][1];
    inverseKey[1][0] = -key[1][0];
    inverseKey[1][1] = key[0][0];
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            inverseKey[i][j] = (inverseKey[i][j] % 26 + 26) % 26;
        }
    }
    
    int plaintext[SIZE];
    plaintext[0] = (inverseKey[0][0] * ciphertext[0] + inverseKey[0][1] * ciphertext[1]) % 26;
    plaintext[1] = (inverseKey[1][0] * ciphertext[0] + inverseKey[1][1] * ciphertext[1]) % 26;

    printf("Decrypted plaintext: %c%c\n", plaintext[0] + 'A', plaintext[1] + 'A');
}

int main() {
    int key[SIZE][SIZE] = {{9, 4}, {5, 7}};
    int ciphertext[SIZE] = {4, 4}; 
    
    decrypt(ciphertext, key);
    
    return 0;
}
