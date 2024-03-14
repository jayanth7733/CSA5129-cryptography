#include <stdio.h>
#include <string.h>
#include <ctype.h>

void monoalphabeticSubstitutionEncrypt(char *message, char *key) {
    int i;
    char ch;

    for (i = 0; message[i] != '\0'; ++i) {
        ch = message[i];

        if (isupper(ch))
            message[i] = key[ch - 'A'];
        else if (islower(ch))
            message[i] = tolower(key[ch - 'a']);
    }
}

int main() {
    char message[100], key[100];
    int i, keyLength;

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);

    printf("Enter key: ");
    fgets(key, sizeof(key), stdin);

    message[strcspn(message, "\n")] = '\0';
    key[strcspn(key, "\n")] = '\0';

    keyLength = strlen(key);

    for (i = 0; message[i] != '\0'; ++i) {
        int keyIndex = i % keyLength;
        char currentKey = key[keyIndex];

        char substitutionKey[26];
        int j;
        for (j = 0; j < 26; ++j) {
            substitutionKey[j] = 'A' + (currentKey + j - 'A') % 26;
        }

        monoalphabeticSubstitutionEncrypt(&message[i], substitutionKey);
    }

    printf("Encrypted message: %s\n", message);

    return 0;
}
