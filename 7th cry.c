#include <stdio.h>

int main() {
    char ciphertext[] = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83"
                        "(88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8*"
                        ";4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81 (‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;";
    
    for (int i = 0; ciphertext[i] != '\0'; ++i) {
        if (ciphertext[i] == '3') {
            printf("e");
        }
        else if (ciphertext[i] == '†') {
            printf("t");
        }
        else if (ciphertext[i] == '8') {
            printf("h");
        }
        else if (ciphertext[i] == '5') {
            printf("s");
        }
        else if (ciphertext[i] == '6') {
            printf("a");
        }
        else if (ciphertext[i] == ')') {
            printf("n");
        }
        else if (ciphertext[i] == '4') {
            printf("d");
        }
        else if (ciphertext[i] == '‡') {
            printf("r");
        }
        else if (ciphertext[i] == ';') {
            printf("o");
        }
        else if (ciphertext[i] == ':') {
            printf(" ");
        }
        else {
            printf("%c", ciphertext[i]);
        }
    }
    
    return 0;
}
