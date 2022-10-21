// ppm.c
// Řešení IJC-DU1, příklad b), 20.3.2022
// Autor: Richard Kocián, FIT
// Přeloženo: gcc 9.4.0
// Funkce pro načtení .ppm souboru a jeho následné odstranění ze zásobníku

#include "ppm.h"

#define P6_READING_SIZE 4
#define XYSIZES_READING_SIZE 14
#define COLORS_READING_SIZE 6

struct ppm *ppm_read(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        warning_msg("Soubor %s nebyl nalezen...\n", filename);
        return NULL;
    }

    int xsize = 0;
    int ysize = 0;
    int colors = 0;
    char params[P6_READING_SIZE], xysize[XYSIZES_READING_SIZE], colors2[COLORS_READING_SIZE];
    char *ysizep;

    if (fgets(params, P6_READING_SIZE, file) == NULL ||
        fgets(xysize, XYSIZES_READING_SIZE, file) == NULL ||
        fgets(colors2, COLORS_READING_SIZE, file) == NULL) {
        fclose(file);
        warning_msg("Chyba při čtení ze souboru %s...\n", file);
        return NULL;
    }

    if ((strcmp(params, "P6") == 0)) {
        warning_msg("Soubor %s není typu P6...\n", filename);
        fclose(file);
        return NULL;
    }

    strtok(xysize, " ");
    xsize = (int) strtol(xysize, NULL, 0);

    ysizep = strtok(NULL, " ");
    if (ysizep == NULL) {
        warning_msg("Hlavička souboru %s má špatný formát...\n", filename);
        fclose(file);
        return NULL;
    }

    ysize = (int) strtol(ysizep, NULL, 0);

    colors = (int) strtol(colors2, NULL, 0);


    if (colors < 0 || colors > 255) {
        fclose(file);
        warning_msg("Soubor %s má špatný rozsah barev...\n", filename);
        return NULL;
    }

    if (xsize <= 0 || ysize <= 0 || xsize > 8000 || ysize > 8000) {
        fclose(file);
        warning_msg("Soubor %s má špatnou šířku a výšku, max 8000*8000, min 1*1...\n", filename);
        return NULL;
    }

    struct ppm *ppm = calloc(xsize * ysize * 3, sizeof(struct ppm));
    if (ppm == NULL) {
        fclose(file);
        warning_msg("Alokace souboru %s proběhla neúspěšně...\n", filename);
        return NULL;
    }

    ppm->xsize = xsize;
    ppm->ysize = ysize;

    int scannedChar = 0;
    for (int i = 0; (scannedChar = fgetc(file)) != EOF; i++) {
        ppm->data[i] = (char) scannedChar;
        if (i > xsize * ysize * 3) {
            fclose(file);
            free(ppm);
            warning_msg("Špatná data v souboru %s...\n", filename);
            return NULL;
        }
    }

    fclose(file);
    return ppm;

}

void ppm_free(struct ppm *p) {
    free(p);
}
