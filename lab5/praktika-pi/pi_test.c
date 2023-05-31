// pi_test.c
//
// Erabilera:   pi_test   iterazio_kop
///////////////////////////////////////

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "pi_kalkulatu.h"

int main(int argc, char *argv[])
{
    double t, k = 3.0, l = -1.0;
    int i, s;

    if (argc < 2) {
      fprintf(stderr, "%s <iterazio_kopurua>\n", argv[0]);
      exit(1);
    }

    t = 1.0;
    for (i = 0, s = atoi(argv[1]); i < s; i++) {
        funtzioa(&t, &k, &l);
    }
    t *= 4;

    printf("Kalkulatutako Pi: %1.16f,  math.h fitxategiko Pi: %.16f\n", t, M_PI);
    printf("Diferentzia Absolutua: %.16f\n", fabs(M_PI - t));

    return 0;
}
