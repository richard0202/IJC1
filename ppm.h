// ppm.c
// Řešení IJC-DU1, příklad b), 20.3.2022
// Autor: Richard Kocián, FIT
// Přeloženo: gcc 9.4.0
// Rozhraní ppm.c

#ifndef PPM_H
#define PPM_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "error.h"

/** @struct         Struktura ppm
 *  @brief          Tato struktura obsahuje šířku a výšku .ppm souboru a jeho data
 *
 *  @param xsize    Šířka ppm souboru
 *  @param ysize    Výška ppm souboru
 *  @param data     Data ppm souboru
 */
struct ppm{
    unsigned xsize;
    unsigned ysize;
    char data[];    // RGB bajty, celkem 3*xsize*ysize
};

/**
 * @brief           Načtení souboru do struktury ppm
 *
 * @param filename  Název souboru, ze kterého se bude číst
 * @return          ppm struktura obsahující výšku, šířku a data souboru
 */
struct ppm * ppm_read(const char * filename);

/**
 * @brief           Uvolnění ppm struktury ze zásobníku
 *
 * @param p         ppm struktura
 */
void ppm_free(struct ppm *p);

#endif //PPM_H
