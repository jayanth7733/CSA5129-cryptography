#include <stdio.h>
#include <string.h>
#include <ctype.h>

void findPosition(char matrix[][5], char ch, int *row, int *col) {
    if (ch == 'J')
        ch = 'I';
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void encryptDigraph(char matrix[][5], char a, char b, char *cipher) {
    int row1, col1, row2, col2;
    findPosition(matrix, a, &row1, &col1);
    findPosition(matrix, b, &row2, &col2);
    if (row1 == row2) { 
        cipher[0] = matrix[row1][(col1 + 1) % 5];
        cipher[1] = matrix[row2][(col2 + 1) % 5];
    } else if (col1 == col2) { 
        cipher[0] = matrix[(row1 + 1) % 5][col1];
        cipher[1] = matrix[(row2 + 1) % 5][col2];
    } else {
        cipher[0] = matrix[row1][col2];
        cipher[1] = matrix[row2][col1];
    }
}

void preprocessPlaintext(char *plaintext) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i++) {
        if (plaintext[i] == ' ')
            strcpy(&plaintext[i], &plaintext[i + 1]); 
    }
    len = strlen(plaintext);
    for (int i = 0; i < len - 1; i += 2) {
        if (plaintext[i] == plaintext[i + 1]) {
            for (int j = len; j > i + 1; j--) {
                plaintext[j] = plaintext[j - 1]; 
            }
            plaintext[i + 1] = 'X'; 
            plaintext[len + 1] = '\0';
            len++;
        }
    }
    if (len % 2 != 0) { 
        plaintext[len] = 'X';
        plaintext[len + 1] = '\0';
    }
}

void encryptPlayfair(char matrix[][5], char *plaintext, char *ciphertext) {
    preprocessPlaintext(plaintext);
    int len = strlen(plaintext);
    for (int i = 0; i < len; i += 2) {
        encryptDigraph(matrix, plaintext[i], plaintext[i + 1], &ciphertext[i]);
    }
}

int main() {
    char matrix[5][5] = {
        {'M', 'F', 'H', 'I', 'K'},
        {'U', 'N', 'O', 'P', 'Q'},
        {'Z', 'V', 'W', 'X', 'Y'},
        {'E', 'L', 'A', 'R', 'G'},
        {'D', 'S', 'T', 'B', 'C'}
    };
    char plaintext[] = "Must see you over Cadogan West. Coming at once.";
    char ciphertext[strlen(plaintext)];

    encryptPlayfair(matrix, plaintext, ciphertext);
    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
