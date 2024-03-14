#include <stdio.h>
#include <string.h>
#include <ctype.h>

void generateCipherSequence(char keyword[], char cipherSequence[]) {
    strcpy(cipherSequence, keyword);
    
    int used[26] = {0};
    
    for (int i = 0; i < strlen(keyword); i++) {
        if (isalpha(keyword[i])) {
            int index = toupper(keyword[i]) - 'A';
            used[index] = 1;
        }
    }
    
    for (char c = 'A'; c <= 'Z'; c++) {
        if (!used[c - 'A']) {
            strncat(cipherSequence, &c, 1);
        }
    }
}

void encrypt(char plaintext[], char cipherSequence[]) {
    for (int i = 0; i < strlen(plaintext); i++) {
        if (isalpha(plaintext[i])) {
            char upper = toupper(plaintext[i]);
            int index = upper - 'A';
            if (index >= 0 && index < 26) {
                plaintext[i] = isupper(plaintext[i]) ? cipherSequence[index] : tolower(cipherSequence[index]);
            }
        }
    }
}

void decrypt(char ciphertext[], char cipherSequence[]) {
    for (int i = 0; i < strlen(ciphertext); i++) {
        if (isalpha(ciphertext[i])) {
            char upper = toupper(ciphertext[i]);
            char *ptr = strchr(cipherSequence, upper);
            if (ptr != NULL) {
                int index = ptr - cipherSequence;
                ciphertext[i] = isupper(ciphertext[i]) ? 'A' + index : 'a' + index;
            }
        }
    }
}

int main() {
    char keyword[] = "CIPHER";
    char cipherSequence[26];
    char plaintext[] = "Hello, World!";
    char ciphertext[100];
    
    generateCipherSequence(keyword, cipherSequence);
    printf("Cipher sequence: %s\n", cipherSequence);
    
    strcpy(ciphertext, plaintext);
    encrypt(ciphertext, cipherSequence);
    printf("Encrypted ciphertext: %s\n", ciphertext);
    
    decrypt(ciphertext, cipherSequence);
    printf("Decrypted plaintext: %s\n", ciphertext);
    
    return 0;
}
