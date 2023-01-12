#ifndef _RANDOM_H
#define _RANDOM_H

#include <iostream>
#include <time.h>


/**
 * Genera un numero intero casuale compreso fra min e max inclusi gli
 * estremi.
 *
 * @param min: Valore minimo
 * @param max: Valore massimo
 * @return Intero compreso fra min e max inclusi
 */
int random(int min, int max)
{
    static bool first = true;
    if (first) {
        srand( time(NULL) ); //seeding for the first time only!
        first = false;
    }
    return min + rand() % (( max + 1 ) - min);
}

#endif // _RANDOM_H
