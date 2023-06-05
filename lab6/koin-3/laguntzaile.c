/* erlojua.c */
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#define COLOR "\e[0;36m" // printf-en erabiltzeko: mezuak CYAN kolorean
#define NOCOLOR "\e[0m"  //

int main(int argc, char *argv[]) {
    int segundo_kopurua;
    long pid_process;
    if (argc!=3) {
        fprintf(stderr, COLOR"Programak ez ditu beharrezko parametroak jaso: ./erlojua segundo_kopurua pid_process\n"NOCOLOR);
        return EXIT_FAILURE;
    }
    segundo_kopurua = atoi(argv[1]); // parametroak jaso
    pid_process = atoi(argv[2]);
    printf(COLOR"Prozesu erlojua naiz eta %lu prozesurako exekuzio-denbora maximoa (%d) kontrolatuko dut\n"NOCOLOR,
            pid_process, segundo_kopurua);
    sleep(segundo_kopurua);
    printf(COLOR"Prozesu erlojua naiz: denbora agortu da (%d segundu) "NOCOLOR, segundo_kopurua);
    if (kill(pid_process,SIGTERM)==0) {
        printf(COLOR"eta prozesu umeak martxan jarraitzen du\n"NOCOLOR);
    } else {
        printf(COLOR"prozesu umea dagoeneko amaitu da\n"NOCOLOR);
    }
    return EXIT_SUCCESS;
}
