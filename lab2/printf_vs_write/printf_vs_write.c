/* printf_vs_write.c */

#include <stdio.h>

main (int argc, char *argv[]) {
    int i;
    for (i=0;i<3;i++) printf("printf ");   // Idatzi 'printf' hiru aldiz
    printf("\n");
    for (i=0;i<3;i++) write(1,"write ",6); // Idatzi 'write' hiru aldiz
    write(1,"\n",1);
}
