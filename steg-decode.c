// steg-decode.c
// Řešení IJC-DU1, příklad b), 20.3.2022
// Autor: Richard Kocián, FIT
// Přeloženo: gcc 9.4.0
// Dekódování .ppm

#include <stdio.h>
#include "ppm.h"
#include "bitset.h"
#include "error.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        error_exit("Špatný počet argumentů!\n");
    }
    struct ppm *ppm;
    ppm = ppm_read(argv[1]);
    if (ppm == NULL) {
        error_exit("ppm_read: Nepodařilo se načíst soubor!\n");
    }
    bitset_alloc(ppm_array, ppm->xsize*ppm->ysize*3);
    Eratosthenes(ppm_array);
    int bit = 0;
    bitset_create(char_array,8);

    for (unsigned int i = 29; i < ppm_array[0]; i++) {
        if (bitset_getbit(ppm_array,i) == 0) {
            bitset_setbit(char_array,bit,(1 & ppm->data[i]));
            bit++;
            if (bit == 8) {
                if (char_array[1] == '\0') {
                    printf("\n");
                    break;
                }
                printf("%c", (char) char_array[1]);
                bit = 0;
            }
        }
    }
    bitset_free(ppm_array);
    ppm_free(ppm);

    return 0;
}
