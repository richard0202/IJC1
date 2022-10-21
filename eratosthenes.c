// eratosthenes.c
// Řešení IJC-DU1, příklad a), 18.3.2022
// Autor: Richard Kocián, FIT
// Přeloženo: gcc 9.4.0
// Algoritmus Eratosthenova síta

#include <math.h>
#include "bitset.h"

void Eratosthenes(bitset_t pole) {
    unsigned long size = bitset_size(pole);

    bitset_setbit(pole,0,1);
    bitset_setbit(pole,1,1);

    for (unsigned long i = 2; i <= (unsigned long) sqrt((double)size) ; i++) {
        if (bitset_getbit(pole,i) == 0) {
            for (unsigned long j = i*i; j < size ; j+=i) {
                bitset_setbit(pole,j,1);
            }
        }

    }
}
