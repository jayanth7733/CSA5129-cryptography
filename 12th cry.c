#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int charToIndex(char c) {
    return toupper(c) - 'A';
}

char indexToChar(int index) {
    return index + 'A';
}

void multiplyMatrix(int A[2][2], int B[2], int result[2]) {
    result[0] = (A[0][0] * B[0] + A[0][1] * B[1]) % 26;
    result[1] = (A[1][0] * B[0] + A[1][1] * B[1]) % 26;
}

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int modInverse(int a, int m) {
    a = (a % m + m) % m; 
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1; 
}

int main() {
    int key[2][2] = {{9, 4}, {5, 7}};

    char plaintext[] = "meet me at the usual place at ten rather than eight oclock";
    int plaintextLength = strlen(plaintext);

    char processedPlaintext[100] = "";
    int index = 0;
    for (int i = 0; i < plaintextLength; i++) {
        if (isalpha(plaintext[i])) {
            processedPlaintext[index++] = toupper(plaintext[i]);
        }
    }
    int processedPlaintextLength = index;

    if (processedPlaintextLength % 2 != 0) {
        processedPlaintext[processedPlaintextLength++] = 'X';
    }
    processedPlaintext[processedPlaintextLength] = '\0';

    int plaintextIndices[100];
    for (int i = 0; i < processedPlaintextLength; i++) {
        plaintextIndices[i] = charToIndex(processedPlaintext[i]);
    }

    printf("Encrypted ciphertext: ");
    for (int i = 0; i < processedPlaintextLength; i += 2) {
        int plaintextVector[2] = {plaintextIndices[i], plaintextIndices[i + 1]};
        int ciphertextVector[2];
        multiplyMatrix(key, plaintextVector, ciphertextVector);
        printf("%c%c", indexToChar(ciphertextVector[0]), indexToChar(ciphertextVector[1]));
    }
    printf("\n");

    return 0;
}
