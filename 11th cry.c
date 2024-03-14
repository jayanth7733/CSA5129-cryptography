#include <stdio.h>

long long factorial(int n) {
    long long fact = 1;
    for (int i = 1; i <= n; ++i) {
        fact *= i;
    }
    return fact;
}

int main() {
    int n = 25;
    long long total_keys = factorial(n);
    long long unique_keys = total_keys / (1 << 4); 
    
    printf("Number of possible keys: %lld\n", total_keys);
    printf("Number of effectively unique keys: %lld\n", unique_keys);

    return 0;
}
