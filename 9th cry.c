#include <stdio.h>
#include <string.h>
#include <ctype.h>

void findPosition(char keyTable[5][5], char letter, int *row, int *col) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (keyTable[i][j] == letter) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void decryptPair(char keyTable[5][5], char pair[2]) {
    int row1, col1, row2, col2;
    findPosition(keyTable, pair[0], &row1, &col1);
    findPosition(keyTable, pair[1], &row2, &col2);
    
    if (row1 == row2) {
        pair[0] = keyTable[row1][(col1 - 1 + 5) % 5];
        pair[1] = keyTable[row2][(col2 - 1 + 5) % 5];
    }
    else if (col1 == col2) {
        pair[0] = keyTable[(row1 - 1 + 5) % 5][col1];
        pair[1] = keyTable[(row2 - 1 + 5) % 5][col2];
    }
    else {
        pair[0] = keyTable[row1][col2];
        pair[1] = keyTable[row2][col1];
    }
}

void decrypt(char ciphertext[], char keyTable[5][5]) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i += 2) {
        if (i + 1 == len) {
            ciphertext[i + 1] = 'X';
        }
        decryptPair(keyTable, &ciphertext[i]);
    }
}

int main() {
    char ciphertext[] = "KXJEY UREBE ZWEHE WRYTU HEYFS\nKREHE GOYFI WTTTU OLKSY CAJPO\nBOTEI ZONTX BYBNT GONEY CUZWR\nGDSON SXBOU YWRHE BAAHY USEDQ";
    char keyTable[5][5] = {
        {'P', 'L', 'A', 'Y', 'F'},
        {'I', 'R', 'E', 'X', 'M'},
        {'B', 'C', 'D', 'G', 'H'},
        {'K', 'N', 'O', 'Q', 'S'},
        {'T', 'U', 'V', 'W', 'Z'}
    };
    
    for (int i = 0; ciphertext[i] != '\0'; ++i) {
        ciphertext[i] = toupper(ciphertext[i]);
    }

    decrypt(ciphertext, keyTable);
    
    printf("Decrypted message:\n%s\n", ciphertext);
    
    return 0;
}
