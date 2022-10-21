// bitset.h
// Řešení IJC-DU1, příklad a), 18.3.2022
// Autor: Richard Kocián, FIT
// Přeloženo: gcc 9.4.0
// Rozhraní bitset.h

#ifndef BITSET_H
#define BITSET_H

#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include "error.h"

typedef unsigned long bitset_t[];

typedef unsigned long bitset_index_t;

#define UNSIGNED_LONG_BIT_COUNT (sizeof(unsigned long) * __CHAR_BIT__)

/**
 * @brief           Na bitech, jejichž index je prvočíslo, nastaví hodnotu 1
 *
 * @param pole      Pole bitů (unsigned long)
 */
void Eratosthenes(bitset_t pole);

/**
 * @brief                Vytvoření lokálního bitového pole
 *
 * @param jmeno_pole      Název pole, které bude vytvořeno
 * @param velikost        Velikost pole
 */
#define bitset_create(jmeno_pole, velikost) \
static_assert((((velikost) > 0)), "chyba při překladu"); \
static_assert(((unsigned long) (velikost) < UINT_FAST64_MAX), "chyba při překladu");                                            \
unsigned long (jmeno_pole)[(((velikost)/ UNSIGNED_LONG_BIT_COUNT) + overflow(velikost) + 1)] = {velikost, 0};

/**
 * @brief                Vytvoření dynamického bitového pole
 *
 * @param jmeno_pole      Název pole, které bude vytvořeno
 * @param velikost        Velikost pole
 */
#define bitset_alloc(jmeno_pole, velikost) \
assert((((velikost) > 0))); \
assert(((unsigned long) (velikost) < UINT_FAST64_MAX)); \
unsigned long *(jmeno_pole) = calloc((((velikost)/ UNSIGNED_LONG_BIT_COUNT) + overflow(velikost) + 1), sizeof(unsigned long));                                   \
if ((jmeno_pole) == NULL) {                \
error_exit("bitset_alloc: Chyba alokace paměti");\
}                                          \
(jmeno_pole)[0] = velikost

#define overflow(velikost) ((velikost) % UNSIGNED_LONG_BIT_COUNT ? 1 : (2))

#ifndef USE_INLINE

/**
 * @brief               Uvolnění pole ze zásobníku
 *
 * @param jmeno_pole    Pole bitů (unsigned long)
 */
#define bitset_free(jmeno_pole) free(jmeno_pole)

/**
 * @brief               Získání velikosti pole
 *
 * @param jmeno_pole    Pole bitů (unsigned long)
 * @return              Velikost pole (unsigned long)
 */
#define bitset_size(jmeno_pole)  (1 ? (jmeno_pole)[0] : 0)

/**
 * @brief               Nastavení hodnoty bitu na daném indexu
 *
 * @param jmeno_pole    Pole bitů (unsigned long)
 * @param index         Index bitu (unsigned long)
 */
#define bitset_setbit(jmeno_pole, index, vyraz) \
if ((unsigned long) (index) >= (bitset_size(jmeno_pole))) {    \
error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu", (unsigned long)(index), (unsigned long)(bitset_size(jmeno_pole)-1));                                                \
}                                               \
if (vyraz) {                                    \
((jmeno_pole)[(((index) + UNSIGNED_LONG_BIT_COUNT) / UNSIGNED_LONG_BIT_COUNT)])  = (((jmeno_pole)[(((index) + UNSIGNED_LONG_BIT_COUNT) / UNSIGNED_LONG_BIT_COUNT)]) | (1UL << (((index) + UNSIGNED_LONG_BIT_COUNT) % UNSIGNED_LONG_BIT_COUNT) ));                                            \
}   else {                                      \
((jmeno_pole)[(((index) + UNSIGNED_LONG_BIT_COUNT) / UNSIGNED_LONG_BIT_COUNT)])  = (((jmeno_pole)[(((index) + UNSIGNED_LONG_BIT_COUNT) / UNSIGNED_LONG_BIT_COUNT)]) & (~(1UL << (((index) + UNSIGNED_LONG_BIT_COUNT) % UNSIGNED_LONG_BIT_COUNT) ))    );                                                    \
}


/**
 * @brief               Získání hodnoty bitu na daném indexu
 *
 * @param jmeno_pole    Pole bitů (unsigned long)
 * @param index         Index bitu (unsigned long)
 * @return              Velikost pole (unsigned long)
 */
#define bitset_getbit(jmeno_pole, index) ( ((unsigned long) (index) >= (bitset_size(jmeno_pole))) ? ((error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", (unsigned long)(index), (unsigned long)(bitset_size(jmeno_pole)-1))),0)   :  (getbit((jmeno_pole), (index))))

#define getbit(jmeno_pole, index) ( (jmeno_pole)[((index) + UNSIGNED_LONG_BIT_COUNT) / UNSIGNED_LONG_BIT_COUNT] & (1UL << (((index) + UNSIGNED_LONG_BIT_COUNT) % UNSIGNED_LONG_BIT_COUNT) ) ? 1 : 0)

#else

/**
 * @brief               Uvolnění pole ze zásobníku
 *
 * @param jmeno_pole    Pole bitů (unsigned long)
 */
inline void bitset_free(bitset_t jmeno_pole) {
    free(jmeno_pole);
}

/**
 * @brief               Získání velikosti pole
 *
 * @param jmeno_pole    Pole bitů (unsigned long)
 * @return              Velikost pole (unsigned long)
 */
inline unsigned long bitset_size(bitset_t jmeno_pole) {
    return jmeno_pole[0];
}

/**
 * @brief               Nastavení hodnoty bitu na daném indexu
 *
 * @param jmeno_pole    Pole bitů (unsigned long)
 * @param index         Index bitu (unsigned long)
 */
inline void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index, int vyraz) {
    if (index >= bitset_size(jmeno_pole)) {
        error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", index, (bitset_size(jmeno_pole)-1));
    }
    bitset_index_t i = ((index + UNSIGNED_LONG_BIT_COUNT) / UNSIGNED_LONG_BIT_COUNT);
    unsigned int position = (index + UNSIGNED_LONG_BIT_COUNT) % UNSIGNED_LONG_BIT_COUNT;
    unsigned long expression = 1;
    expression = expression << position;
    if (vyraz) {
        jmeno_pole[i] = jmeno_pole[i] | expression;
    } else {
        expression = ~expression;
        (jmeno_pole)[i] = jmeno_pole[i] & expression;
    }
}

/**
 * @brief               Získání hodnoty bitu na daném indexu
 *
 * @param jmeno_pole    Pole bitů (unsigned long)
 * @param index         Index bitu (unsigned long)
 * @return              Velikost pole (unsigned long)
 */
inline int bitset_getbit(bitset_t jmeno_pole, bitset_index_t index) {
    if (index >= bitset_size(jmeno_pole)) {
        error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", index, (bitset_size(jmeno_pole)-1));
    }
    bitset_index_t i = ((index + UNSIGNED_LONG_BIT_COUNT) / UNSIGNED_LONG_BIT_COUNT);
    unsigned int position = (index + UNSIGNED_LONG_BIT_COUNT) % UNSIGNED_LONG_BIT_COUNT;
    unsigned long expression = 1;
    expression = expression << position;
    if (jmeno_pole[i] & expression) {
        return 1;
    } else {
        return 0;
    }
}


#endif
#endif //BITSET_H
