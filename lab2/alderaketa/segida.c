#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIGT_ZBK 10

int main(int argc, char *argv[]) {
    int i;
    int n=1;
    char text[MAX_DIGT_ZBK];
    if (argc==2) n = atoi(argv[1]); // parametroa jaso
    for (i=1;i<=n;i++) {            // for 1 to 'jasotako parametrora'
      sprintf(text, "%d\n", i);   // idatzi beharreko testua: zenbakia + lerro_jauzia
      //  write(1,text,strlen(text)); // idatzi sistema-deia erabiliz
         printf("%s",text);    // idatzi liburutegiko funtzioa erabiliz
    }
    return 0;
}
