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

void letterFrequencyAttack(char ciphertext[], int topN) {
    int frequency[ALPHABET_SIZE] = {0};
    calculateFrequency(ciphertext, frequency);

    int originalFrequency[ALPHABET_SIZE];
    memcpy(originalFrequency, frequency, ALPHABET_SIZE * sizeof(int));

    int sortedIndices[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        sortedIndices[i] = i;
    }
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (frequency[sortedIndices[i]] < frequency[sortedIndices[j]]) {
                int temp = sortedIndices[i];
                sortedIndices[i] = sortedIndices[j];
                sortedIndices[j] = temp;
            }
        }
    }

    char commonLetters[] = {'e', 't', 'a', 'o', 'i', 'n', 's', 'h', 'r', 'd', 'l', 'c', 'u', 'm', 'w', 'f', 'g', 'y', 'p', 'b', 'v', 'k', 'j', 'x', 'q', 'z'};
    
    printf("Top %d possible plaintexts:\n", topN);
    for (int k = 0; k < topN; k++) {
        int shift = sortedIndices[k];
        char plaintext[strlen(ciphertext) + 1];
        for (int i = 0; i < strlen(ciphertext); i++) {
            if (isalpha(ciphertext[i])) {
                char base = isupper(ciphertext[i]) ? 'A' : 'a';
                plaintext[i] = ((ciphertext[i] - base - shift + ALPHABET_SIZE) % ALPHABET_SIZE) + base;
            } else {
                plaintext[i] = ciphertext[i];
            }
        }
        plaintext[strlen(ciphertext)] = '\0';
        printf("%s\n", plaintext);
    }
}

int main() {
    char ciphertext[] = "Qeb nrfzh yoltk clu grjmp lsbo qeb ixwv ald.";

    int topN;
    printf("Enter the number of possible plaintexts to display: ");
    scanf("%d", &topN);

    letterFrequencyAttack(ciphertext, topN);

    return 0;
}
