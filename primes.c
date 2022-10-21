// primes.c
// Řešení IJC-DU1, příklad a), 18.3.2022
// Autor: Richard Kocián, FIT
// Přeloženo: gcc 9.4.0
// Výpis prvočísel z N čísel

#include <stdio.h>
#include <time.h>
#include "bitset.h"

#define N 300000000

int main() {
    clock_t start_t;
    start_t = clock();
    bitset_alloc(pole, N);
    unsigned long size = bitset_size(pole);
    Eratosthenes(pole);

    unsigned long final[10] = {0,};
    int count = 0;
    for (unsigned long i = size - 1; count < 10; i--) {
        if (bitset_getbit(pole, i) == 0) {
            final[count] = i;
            count++;
        }
    }

    for (int i = 9; i >= 0; i--) {
        printf("%lu\n", final[i]);
    }

    bitset_free(pole);
    fprintf(stderr, "Time=%.3g\n", (double) (clock() - start_t) / CLOCKS_PER_SEC);

    return 0;
}
