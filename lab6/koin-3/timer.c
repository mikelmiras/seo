/* nire_sleep.h fitxategia */
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void alarma_kudeatzailea(int seinalea) {
    // printf("Alarma seinalea jaso da eta tratatzen ari da\n");
    return;
}

int nire_sleep(int segundo_kopurua) {
    if (segundo_kopurua<1) segundo_kopurua = 1;   // balio minimoa ezarri
    signal(SIGALRM, alarma_kudeatzailea); // lotu funtzioa SIGALRM seinalearekin
    alarm(segundo_kopurua);   // timer-a hasieratu
    pause();                  // gelditu exekuzioa seinale bat jaso arte
    return(alarm(0));
}
