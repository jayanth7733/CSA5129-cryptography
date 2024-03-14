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
    char message[100], key[26];
    int i;

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);

    printf("Enter key (a string of 26 characters, each representing a unique letter of the ciphertext alphabet): ");
    fgets(key, sizeof(key), stdin);

    message[strcspn(message, "\n")] = '\0';
    key[strcspn(key, "\n")] = '\0';

    if (strlen(key) != 26) {
        printf("Error: Key length must be 26.\n");
        return 1;
    }

    for (i = 0; i < 26; ++i) {
        if (!isalpha(key[i])) {
            printf("Error: Key must contain only alphabetic characters.\n");
            return 1;
        }
    }

    int freq[26] = {0};
    for (i = 0; i < 26; ++i) {
        if (isupper(key[i]))
            freq[key[i] - 'A']++;
        else
            freq[key[i] - 'a']++;
    }
    for (i = 0; i < 26; ++i) {
        if (freq[i] != 1) {
            printf("Error: Key must contain each letter of the alphabet exactly once.\n");
            return 1;
        }
    }

    monoalphabeticSubstitutionEncrypt(message, key);

    printf("Encrypted message: %s\n", message);

    return 0;
}
