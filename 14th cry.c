#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void encrypt(char plaintext[], int key[], int keyLength) {
    int plaintextLength = strlen(plaintext);
    char ciphertext[plaintextLength + 1];
    strcpy(ciphertext, plaintext);

    for (int i = 0; i < plaintextLength; i++) {
        if (isalpha(plaintext[i])) {
            int shift = key[i % keyLength]; 
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            ciphertext[i] = ((plaintext[i] - base + shift) % 26) + base; 
        }
    }

    printf("Encrypted ciphertext: %s\n", ciphertext);
}

void decrypt(char ciphertext[], int key[], int keyLength) {
    int ciphertextLength = strlen(ciphertext);
    char plaintext[ciphertextLength + 1];
    strcpy(plaintext, ciphertext);

    for (int i = 0; i < ciphertextLength; i++) {
        if (isalpha(ciphertext[i])) {
            int shift = key[i % keyLength]; 
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = ((ciphertext[i] - base - shift + 26) % 26) + base; 
        }
    }

    printf("Decrypted plaintext: %s\n", plaintext);
}

int main() {
    char plaintext[] = "sendmoremoney";
    int key[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    int keyLength = sizeof(key) / sizeof(key[0]);

    encrypt(plaintext, key, keyLength);

    char ciphertext[] = "KWOJCTVVAPVNJL"; 
    printf("Ciphertext produced in part (a): %s\n", ciphertext);

    int originalKey[keyLength];
    for (int i = 0; i < keyLength; i++) {
        originalKey[i] = (ciphertext[i] - 'A' - (plaintext[i] - 'A') + 26) % 26;
    }

    decrypt(ciphertext, originalKey, keyLength);

    return 0;
}
