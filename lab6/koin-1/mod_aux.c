#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>
#include "config.h"

// Irteera kolore desberdinez adierazteko (testuaren hasieran idatzi behar)
#define COLOR_PROMPT "\033[0;35m" // printf-en erabiltzeko: mezuak CYAN  kolorean
#define COLOR_KOIN  "\033[0;36m" // printf-en erabiltzeko: mezuak CYAN  kolorean
#define COLOR_CHILD "\033[0;32m" // printf-en erabiltzeko: mezuak GREEN kolorean
#define COLOR_ERROR "\033[0;31m" // printf-en erabiltzeko: mezuak RED   kolorean
#define NOCOLOR     "\033[0m"    // kolore normala

void printf_trace (int umea, const char * format, ... );
// errore mezua erakutsi eta atera
void errorea_tratatu ( const char * format, ... );

// tag::irakurri_agindua[]
ssize_t irakurri_agindua(char *prompt, char *agindua)
{
  // irakurri hurrengo agindua, irakurritako aginduaren karaktere kopurua itzuliz
  // Lehenengo pausua sarrerako parametro mduan jasotako prompt-a idaztea izango da
  char mezua_prompt[MAX_PROMPT_LUZERA+10]; // prompt-aren luzera maximoa + prompt-a koloztatzeko color codes
  sprintf(mezua_prompt, "%s%s%s", COLOR_PROMPT, prompt, NOCOLOR); // koloreak gehitu
  write(STDOUT_FILENO, mezua_prompt, strlen(mezua_prompt));
  // printf("%s", mezua);fflush(stdout); Beste aukera bat, liburutegiko printf funtzioa erabiliz
  // Hurrengo pausua agindua irakurtzea izango da
  ssize_t karaktere_kop = read(STDIN_FILENO, agindua, MAX_AGIND_LUZERA-1);
  if (karaktere_kop==0) 
  {
    printf_trace(gurasoa, "Aginduen bukaera => ateratzen");
    return 0;
  }
  if (agindua[karaktere_kop-1] != '\n') 
  {
    /* koin bertsio honetan aginduak lerroka adierazten dira.
      Hortaz, aginduaren bukaeran "\n" karakterea ez badago,
      aginduaren zati bat baino ez dago bufferrean ('agindua' aldagaia),
      Egoera hau sortzen da erabiltzaileak teklatutik idatzitako aginduaren
      luzera handiagoa denan agindua adierazteko erazagutako karaktere-kate aldagaia baino ('agindua')
      Hortaz, agindua honen exekuzioa bertan behera utzi eta agindu hutsa jartzen da */
    printf("Aginduaren luzera maximoa (%d) gainditu da. Erabili agindu laburragoak\n", MAX_AGIND_LUZERA);
    strcpy(agindua, " \0");  // agindu hutsa adierazi. Karaktere bat jarri aginduen sarrera- amaiera ez interpretatzeko
    return strlen(agindua);
  }
  // karakterea kateari bukaera-marka (\0) gehitzen da bukaeran, 
  // string bezala tratatu ahal izateko
  if (karaktere_kop>0) agindua[karaktere_kop-1] = '\0';
  // Debug: idatzi teklatutik irakurritako karaktere-katea (agindua)
  #if TRACE_MESSAGES == 1 
    int i; char mezua_trace[3 * karaktere_kop + 1];
    mezua_trace[0] = '\0';
    for (i=0; i<karaktere_kop-1; i++) { // karaktere guztiak aztertu, bukaera marka izan ezik
        if ((strlen(mezua_trace)+3) >= sizeof(mezua_trace)) {break;} // string-aren tamaina gainditzen da
        sprintf(mezua_trace + strlen(mezua_trace), "[%c]", agindua[i]);
    }
    printf_trace(gurasoa, "Irakurritako agindua string formatuan: %s\n", mezua_trace);
  #endif
  return karaktere_kop;
}
// end::irakurri_agindua[]

// tag::eskuratu_argumentuak[]
int eskuratu_argumentuak(char *agindua_string, char *arg_array[])
{
  static char buf_agindua_backup[MAX_AGIND_LUZERA];  // irakurritako agindua metatzeko (originala aldatu gabe)
  strcpy(buf_agindua_backup, agindua_string);
  printf("Aginduaren kopia '%s' da\n", buf_agindua_backup);

  char *argumentua;
  // argumentu bezala interpretatu behar ez diren karaktereak => bereizleak
  char *arg_bereizleak = " \t;&";
  int num_arg = 0;
  // eskuratu argumentuak bereizleak erabiliz
  argumentua = strtok(buf_agindua_backup, arg_bereizleak); 
  while((argumentua != NULL) && (num_arg<MAX_AGIND_ARG))
  {
    arg_array[num_arg++] = argumentua;
    argumentua = strtok(NULL, arg_bereizleak);
  }
  arg_array[num_arg] = NULL; // ez dago argumentu gehiago => espero den bukaera marka jarri arg_array taulan
  // Debug: idatzi pantailan argindua arg formatuan
  #if TRACE_MESSAGES == 1    
    int i; char mezua_trace[MAX_MEZUA_TRACE_ARG]; char string_aux[MAX_MEZUA_TRACE_ARG];
    sprintf(mezua_trace, "Irakurritako agindua arg formatuan: ");
    for (i=0; i<=num_arg; i++)
    {
      sprintf(string_aux, "arg[%d]->\"%s\" ", i, arg_array[i]);
      if ((strlen(mezua_trace) + strlen(string_aux)) >= sizeof(mezua_trace)) {break;} // string-aren tamaina gainditzen da
      strcat(mezua_trace, string_aux);
    }
    printf_trace(gurasoa, "%s\n", mezua_trace);
  #endif
  return num_arg;     // itzuli aurkitutako argumentu kopurua
}
// end::eskuratu_argumentuak[]

void printf_trace (int prozesu_mota, const char * format, ... ) 
{
  #if TRACE_MESSAGES == 1
    char buffer[MAX_MEZUA_TRACE_ARG];
    va_list args;
    va_start (args, format);
    vsprintf (buffer,format, args);
    if (prozesu_mota==gurasoa) fprintf(stderr, COLOR_KOIN "[DEBUG] koin (pid %d): ", getpid());
    else fprintf(stderr, COLOR_CHILD "[DEBUG] CHILD (pid %d): ", getpid());
    fprintf(stderr,"%s" NOCOLOR, buffer); fflush(stderr);
    va_end (args);
  #endif
}

void errorea_tratatu ( const char * format, ... )
{
  char errore_mezua[MAX_MEZUA_TRACE_ARG];
  va_list args;
  va_start (args, format);
  vsprintf (errore_mezua,format, args);
  va_end (args);
  fprintf(stderr, COLOR_ERROR "\n[ERROR] pid %d: ", getpid());
  if (errno!=0) perror(errore_mezua); // erakutsi sistemako errorea gure mezuarekin batera
  else fprintf(stderr, "%s" NOCOLOR, errore_mezua);
  exit(1);
}

