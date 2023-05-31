/* koin.c: komando interpretatzailea */
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <libgen.h>

#include "config.h"
#include "mod_aux.c"

// tag::main[]
int main(int argc, char *argv[])
{
  pid_t fork_emaitza, pid_umea, pid_finished;
  int umea_itzulera_kodea, status;
  char buf_agindua[MAX_AGIND_LUZERA];         // irakurri beharreko agindua metatzeko
  char *agindua_arg_formatuan[MAX_AGIND_ARG]; // irakurritako aginduaren arg formatuan
  char prompt[MAX_PROMPT_LUZERA];  // prompt testua metatzeko(agindua idazterko gonbidapena)
  if (argc==1)
  {
    printf_trace(gurasoa, "%s abiatu da parametrorik gabe\n",basename(argv[0]));
    printf_trace(gurasoa, "Sakatu Control+D bukatzeko\n");
  }
  // prompt-en erabili programaren_izena + "$ "
  sprintf(prompt, "%s$ ", basename(argv[0]));

  // Irakurri erabilatzailearen agindua eta prozesatu
  while (irakurri_agindua(prompt, buf_agindua) > 0)
  {
    // puntu honetan sartuz gero, gutxienez karaktere bat irakurri da 
    // Aginduaren argumentuak eskuratu, 'argv' formatuan gordez
    if (eskuratu_argumentuak(buf_agindua, agindua_arg_formatuan)==0)
    { // argumenturik aurkitu ezean
        printf_trace(gurasoa, "Agindua hutsik\n");
        continue; // while-ren hurrengo interakzioara joan zuzenean
    }
    fork_emaitza = fork();  // sortu prozesua umea <1>
    switch (fork_emaitza)
    {    // aztertu fork funtzioaren emaitza
      case -1:
        errorea_tratatu("Ezin izan da prozesu berririk sortu (fork)\n");
        break;
      case  0: /* Umea bada (fork funtzioak 0 itzultzen du prozesu berriaren kasuan) */
        printf_trace(umea, 
                     "sortu berria. Orain exec '%s ...' exekutatzera...\n", 
                     agindua_arg_formatuan[0]);
        // Prozesu umeari exekutatu behar den programa (agindua) ezarri
        if ((execvp(agindua_arg_formatuan[0], agindua_arg_formatuan))==-1)
            errorea_tratatu("\"exec('%s',...)\" egitean errorea sortu da", 
                            agindua_arg_formatuan[0]);
        errorea_tratatu("Agindu honetara iritsiz gero, exec-en errorea sortuz gero");
        break;
      default: /* gurasoaren kodea */
        pid_umea = fork_emaitza;  // sortutako prozesu umearen pid-a jaso
        printf_trace(gurasoa, "prozesu umea (PID %d) abiatu da\n", pid_umea);
        pid_finished = wait(&status);    // ume bat bukatu arte zain gelditu
        if ( pid_finished != pid_umea)
        { // bukatu den prozesua aurretik sortutakoa ez bada
          errorea_tratatu("PID %d umearen bukaeraren zain, baina PID %d-koa jaso da",
                          pid_umea, pid_finished);
        } else
        {
          if (WIFEXITED(status))
          {        // Jaso itzulera kodea
              umea_itzulera_kodea = WEXITSTATUS(status);
              printf_trace(gurasoa,
                           "prozesu ume bat (PID %d) bukatu da %d itzulera-kodearekin\n",
                          pid_finished, umea_itzulera_kodea);
          }
        }
        break;
    } // switch
  } // while
  printf("\n");
  return 0;
}
// end::main[]

