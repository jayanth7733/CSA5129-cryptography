#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

void calculateFrequency(char text[], int frequency[]) {
    int length = strlen(text);
    for (int i = 0; i < length; i++) {
        if (isalpha(text[i])) {
            char letter = tolower(text[i]);
            frequency[letter - 'a']++;
        }
    }
}

void decrypt(char ciphertext[], int key) {
    int length = strlen(ciphertext);
    char plaintext[length + 1];

    for (int i = 0; i < length; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = ((ciphertext[i] - base - key + ALPHABET_SIZE) % ALPHABET_SIZE) + base;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }

    plaintext[length] = '\0';
    printf("Key: %d, Possible Plaintext: %s\n", key, plaintext);
}

void findLikelyKeys(char ciphertext[], int topN) {
    int frequency[ALPHABET_SIZE] = {0};
    calculateFrequency(ciphertext, frequency);

    int maxFrequency = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (frequency[i] > maxFrequency) {
            maxFrequency = frequency[i];
        }
    }

    for (int key = 1; key < ALPHABET_SIZE; key++) {
        int decryptedFrequency[ALPHABET_SIZE] = {0};
        decrypt(ciphertext, key);
    }
}

int main() {
    char ciphertext[] = "Zpv xbudi tjtufst jt b xbmlt jt efqfoe!";

    int topN;
    printf("Enter the number of possible plaintexts to display: ");
    scanf("%d", &topN);

    findLikelyKeys(ciphertext, topN);

    return 0;
}
