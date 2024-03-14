#include <stdio.h>
#include <string.h>

void caesarCipherEncrypt(char *message, int shift) {
    int i;
    char ch;

    for (i = 0; message[i] != '\0'; ++i) {
        ch = message[i];

        if (ch >= 'A' && ch <= 'Z')
            message[i] = ((ch - 'A' + shift) % 26) + 'A';
        else if (ch >= 'a' && ch <= 'z')
            message[i] = ((ch - 'a' + shift) % 26) + 'a';
    }
}

int main() {
    char message[100];
    int shift, i;

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);

    message[strcspn(message, "\n")] = '\0';

    for (shift = 1; shift <= 25; ++shift) {
        char encryptedMessage[100];
        strcpy(encryptedMessage, message);

        caesarCipherEncrypt(encryptedMessage, shift);

        printf("Shift %d: %s\n", shift, encryptedMessage);
    }

    return 0;
}
