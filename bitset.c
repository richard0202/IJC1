// bitset.c
// Řešení IJC-DU1, příklad a), 18.3.2022
// Autor: Richard Kocián, FIT
// Přeloženo: gcc 9.4.0
// Definice inline funkcí z bitset.h


#include "bitset.h"

#ifdef USE_INLINE

extern inline unsigned long bitset_size(bitset_t jmeno_pole);

extern inline void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index, int vyraz);

extern inline int bitset_getbit(bitset_t jmeno_pole, bitset_index_t index);

extern inline void bitset_free(bitset_t jmeno_pole);

#endif
