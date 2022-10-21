// error.c
// Řešení IJC-DU1, příklad b), 20.3.2022
// Autor: Richard Kocián, FIT
// Přeloženo: gcc 9.4.0
// Funkce pro zobrazení chyby

#include "error.h"

void warning_msg(const char *fmt, ...) {
    va_list arguments;
    va_start(arguments,fmt);
    fprintf(stderr,"CHYBA: ");
    vprintf(fmt, arguments);
    va_end(arguments);
}

void error_exit(const char *fmt, ...) {
    va_list arguments;
    va_start(arguments,fmt);
    fprintf(stderr,"CHYBA: ");
    vprintf(fmt, arguments);
    va_end(arguments);
    exit(1);
}
