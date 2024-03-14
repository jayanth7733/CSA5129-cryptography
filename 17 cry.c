#include <stdio.h>
#include <stdint.h>

const int IP[] = {58, 50, 42, 34, 26, 18, 10, 2,
                   60, 52, 44, 36, 28, 20, 12, 4,
                   62, 54, 46, 38, 30, 22, 14, 6,
                   64, 56, 48, 40, 32, 24, 16, 8,
                   57, 49, 41, 33, 25, 17, 9, 1,
                   59, 51, 43, 35, 27, 19, 11, 3,
                   61, 53, 45, 37, 29, 21, 13, 5,
                   63, 55, 47, 39, 31, 23, 15, 7};

const int FP[] = {40, 8, 48, 16, 56, 24, 64, 32,
                   39, 7, 47, 15, 55, 23, 63, 31,
                   38, 6, 46, 14, 54, 22, 62, 30,
                   37, 5, 45, 13, 53, 21, 61, 29,
                   36, 4, 44, 12, 52, 20, 60, 28,
                   35, 3, 43, 11, 51, 19, 59, 27,
                   34, 2, 42, 10, 50, 18, 58, 26,
                   33, 1, 41, 9, 49, 17, 57, 25};

const int E[] = {32, 1, 2, 3, 4, 5,
                  4, 5, 6, 7, 8, 9,
                  8, 9, 10, 11, 12, 13,
                  12, 13, 14, 15, 16, 17,
                  16, 17, 18, 19, 20, 21,
                  20, 21, 22, 23, 24, 25,
                  24, 25, 26, 27, 28, 29,
                  28, 29, 30, 31, 32, 1};

const int S[8][4][16] = {
    {
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    },
};

const int P[] = {16, 7, 20, 21,
                 29, 12, 28, 17,
                 1, 15, 23, 26,
                 5, 18, 31, 10,
                 2, 8, 24, 14,
                 32, 27, 3, 9,
                 19, 13, 30, 6,
                 22, 11, 4, 25};

const int PC1[] = {57, 49, 41, 33, 25, 17, 9,
                   1, 58, 50, 42, 34, 26, 18,
                   10, 2, 59, 51, 43, 35, 27,
                   19, 11, 3, 60, 52, 44, 36,
                   63, 55, 47, 39, 31, 23, 15,
                   7, 62, 54, 46, 38, 30, 22,
                   14, 6, 61, 53, 45, 37, 29,
                   21, 13, 5, 28, 20, 12, 4};

const int PC2[] = {14, 17, 11, 24, 1, 5, 3, 28,
                   15, 6, 21, 10, 23, 19, 12, 4,
                   26, 8, 16, 7, 27, 20, 13, 2,
                   41, 52, 31, 37, 47, 55, 30, 40,
                   51, 45, 33, 48, 44, 49, 39, 56,
                   34, 53, 46, 42, 50, 36, 29, 32};

const int shifts[] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

void initialPermutation(uint64_t *block) {
    uint64_t result = 0;
    for (int i = 0; i < 64; i++) {
        result |= ((*block >> (64 - IP[i])) & 1) << (63 - i);
    }
    *block = result;
}

void finalPermutation(uint64_t *block) {
    uint64_t result = 0;
    for (int i = 0; i < 64; i++) {
        result |= ((*block >> (64 - FP[i])) & 1) << (63 - i);
    }
    *block = result;
}

void expansion(uint32_t *r, uint64_t *expanded) {
    *expanded = 0;
    for (int i = 0; i < 48; i++) {
        *expanded |= ((*r >> (32 - E[i])) & 1) << (47 - i);
    }
}

void sBox(uint64_t expanded, uint32_t *output) {
    *output = 0;
    for (int i = 0; i < 8; i++) {
        int row = ((expanded & (0x20 | (0x1 << (5 * i)))) >> (4 + 6 * i)) | ((expanded & (0x1 << (6 * i))) >> (6 * i));
        int col = (expanded >> (5 + 6 * i)) & 0xF;
        *output |= (uint32_t)S[i][row][col] << (28 - 4 * i);
    }
}

void permutation(uint32_t *block) {
    uint32_t result = 0;
    for (int i = 0; i < 32; i++) {
        result |= ((*block >> (32 - P[i])) & 1) << (31 - i);
    }
    *block = result;
}

void generateSubkeys(uint64_t key, uint64_t *subkeys) {
    uint64_t permutedKey = 0;
    for (int i = 0; i < 56; i++) {
        permutedKey |= ((key >> (64 - PC1[i])) & 1) << (55 - i);
    }

    uint32_t c = (uint32_t)(permutedKey >> 28);
    uint32_t d = (uint32_t)(permutedKey & 0xFFFFFFF);

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < shifts[15 - i]; j++) {
            uint32_t shiftedC = (c << 1) | (c >> 27);
            uint32_t shiftedD = (d << 1) | (d >> 27);
            c = shiftedC & 0xFFFFFFF;
            d = shiftedD & 0xFFFFFFF;
        }

        uint64_t cd = ((uint64_t)c << 28) | (uint64_t)d;
        subkeys[i] = 0;
        for (int j = 0; j < 48; j++) {
            subkeys[i] |= ((cd >> (56 - PC2[j])) & 1) << (47 - j);
        }
    }
}

void feistel(uint32_t *r, uint64_t subkey) {
    uint64_t expanded = 0;
    expansion(r, &expanded);

    expanded ^= subkey;

    uint32_t output = 0;
    sBox(expanded, &output);

    permutation(&output);

    *r ^= output;
}

void desDecrypt(uint64_t *block, uint64_t *subkeys) {
    initialPermutation(block);

    uint32_t l = (uint32_t)(*block >> 32);
    uint32_t r = (uint32_t)(*block);

    for (int i = 15; i >= 0; i--) {
        uint32_t temp = r;
        feistel(&r, subkeys[i]);
        r ^= l;
        l = temp;
    }

    *block = ((uint64_t)r << 32) | (uint64_t)l;

    finalPermutation(block);
}

int main() {
    uint64_t ciphertext = 0x85E813540F0AB405;

    uint64_t key = 0x133457799BBCDFF1;

    uint64_t subkeys[16];
    generateSubkeys(key, subkeys);

    desDecrypt(&ciphertext, subkeys);

    printf("Decrypted plaintext: %llx\n", ciphertext);

    return 0;
}
