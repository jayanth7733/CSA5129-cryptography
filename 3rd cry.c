#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void preprocessKey(char *key) {
    int i, j, k = 0;
    int len = strlen(key);
    char newKey[26] = {0};
    
    for (i = 0; i < len; i++) {
        if (key[i] != ' ')
            newKey[k++] = tolower(key[i]); 
    }

    for (i = 0; i < k; i++) {
        for (j = i + 1; j < k; j++) {
            if (newKey[i] == newKey[j]) {
                for (int l = j; l < k; l++) {
                    newKey[l] = newKey[l + 1];
                }
                k--;
                j--;
            }
        }
    }

    int idx = 0;
    for (i = 'a'; i <= 'z'; i++) {
        if (i == 'j') 
            continue;
        int found = 0;
        for (j = 0; j < k; j++) {
            if (newKey[j] == i) {
                found = 1;
                break;
            }
        }
        if (!found)
            newKey[k++] = i;
    }

    strcpy(key, newKey);
}

void buildKeyMatrix(char *key, char matrix[SIZE][SIZE]) {
    preprocessKey(key);

    int i, j, k = 0;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            matrix[i][j] = key[k++];
        }
    }
}

void findPosition(char matrix[SIZE][SIZE], char ch, int *row, int *col) {
    if (ch == 'j')
        ch = 'i'; // Treat 'j' as 'i'

    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void playfairEncrypt(char matrix[SIZE][SIZE], char ch1, char ch2) {
    int row1, col1, row2, col2;
    findPosition(matrix, ch1, &row1, &col1);
    findPosition(matrix, ch2, &row2, &col2);

    if (row1 == row2) {
        printf("%c%c", matrix[row1][(col1 + 1) % SIZE], matrix[row2][(col2 + 1) % SIZE]);
    } else if (col1 == col2) {
        printf("%c%c", matrix[(row1 + 1) % SIZE][col1], matrix[(row2 + 1) % SIZE][col2]);
    } else {
        printf("%c%c", matrix[row1][col2], matrix[row2][col1]);
    }
}

void performPlayfairEncryption(char matrix[SIZE][SIZE], char *plaintext) {
    int i;
    int len = strlen(plaintext);

    if (len % 2 != 0) {
        plaintext[len] = 'x';
        plaintext[len + 1] = '\0';
        len++;
    }

    for (i = 0; i < len; i += 2) {
        playfairEncrypt(matrix, plaintext[i], plaintext[i + 1]);
    }
}

int main() {
    char key[26], matrix[SIZE][SIZE];
    char plaintext[100];

    printf("Enter key (no spaces, max 25 characters): ");
    fgets(key, sizeof(key), stdin);
    printf("Enter plaintext (no spaces, max 99 characters): ");
    fgets(plaintext, sizeof(plaintext), stdin);

    key[strcspn(key, "\n")] = '\0';
    plaintext[strcspn(plaintext, "\n")] = '\0';

    buildKeyMatrix(key, matrix);

    printf("Encrypted text: ");
    performPlayfairEncryption(matrix, plaintext);
    printf("\n");

    return 0;
}
