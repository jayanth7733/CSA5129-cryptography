#include <stdio.h>
#include <stdint.h>

void generateSubkeys(uint64_t key, uint64_t *subkeys);

int main() {
    uint64_t initialKey = 0x133457799BBCDFF1; 
    uint64_t subkeys[16]; 

    generateSubkeys(initialKey, subkeys);

    printf("Subkeys:\n");
    for (int i = 0; i < 16; i++) {
        printf("Subkey %d: 0x%llx\n", i+1, subkeys[i]);
    }

    return 0;
}

void generateSubkeys(uint64_t key, uint64_t *subkeys) {
    static const int pc1[] = {
        57, 49, 41, 33, 25, 17, 9,
        1, 58, 50, 42, 34, 26, 18,
        10, 2, 59, 51, 43, 35, 27,
        19, 11, 3, 60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15,
        7, 62, 54, 46, 38, 30, 22,
        14, 6, 61, 53, 45, 37, 29,
        21, 13, 5, 28, 20, 12, 4
    };

    static const int pc2[] = {
        14, 17, 11, 24, 1, 5, 3, 28,
        15, 6, 21, 10, 23, 19, 12, 4,
        26, 8, 16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55, 30, 40,
        51, 45, 33, 48, 44, 49, 39, 56,
        34, 53, 46, 42, 50, 36, 29, 32
    };

    uint64_t permutedKey = 0;
    for (int i = 0; i < 56; i++) {
        uint64_t bit = (key >> (64 - pc1[i])) & 0x01;
        permutedKey |= (bit << (55 - i));
    }

    uint32_t left = (permutedKey >> 28) & 0xFFFFFFF;
    uint32_t right = permutedKey & 0xFFFFFFF;

    for (int i = 0; i < 16; i++) {
        int shift = (i < 2 || i == 8 || i == 15) ? 1 : 2;
        left = ((left << shift) | (left >> (28 - shift))) & 0xFFFFFFF;
        right = ((right << shift) | (right >> (28 - shift))) & 0xFFFFFFF;

        uint64_t merged = ((uint64_t)left << 28) | right;

        uint64_t subkey = 0;
        for (int j = 0; j < 48; j++) {
            uint64_t bit = (merged >> (56 - pc2[j])) & 0x01;
            subkey |= (bit << (47 - j));
        }

        subkeys[i] = subkey;
    }
}
