// error.h
// Řešení IJC-DU1, příklad b), 20.3.2022
// Autor: Richard Kocián, FIT
// Přeloženo: gcc 9.4.0
// Rozhraní error.h

#ifndef ERROR_H
#define ERROR_H
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

/**
 * @brief           Zaslání upozornění
 *
 * @param fmt       String upozornění
 */
void warning_msg(const char *fmt, ...);

/**
 * @brief           Zaslání upozornění a ukončení programu
 *
 * @param fmt       String upozornění
 */
void error_exit(const char *fmt, ...);

#endif //ERROR_H
