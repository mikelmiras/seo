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
  char buf_agindua[MAX_AGIND_LUZERA];
char pro;
  // irakurri beharreko agindua metatzeko
  char *agindua_arg_formatuan[MAX_AGIND_ARG]; // irakurritako aginduaren arg formatuan
  char prompt[MAX_PROMPT_LUZERA];  // prompt testua metatzeko(agindua idazterko gonbidapena)
  if (argc==1)
  {
    printf_trace(gurasoa, "%s abiatu da parametrorik gabe\n",basename(argv[0]));
    printf_trace(gurasoa, "Sakatu Control+D bukatzeko\n");
  }


  if (getenv("GONBIDAPEN") == NULL){	
	  char l[100] = "";
	  strcat(l,basename(argv[0]));
	  strcat(l, ":");
	  strcat(l, getenv("PWD"));
  	setenv("GONBIDAPEN", l, 1);
  }
  // prompt-en erabili programaren_izena + "$ "
  sprintf(prompt, "%s$ ", getenv("GONBIDAPEN"));
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
    
    if (strcmp(agindua_arg_formatuan[0], "exit") == 0){
	    kill(0, 9);
	    return;
    }else{
    if (strcmp(agindua_arg_formatuan[0], "esleitu") == 0){
    
	// Aldatu
	printf_trace(gurasoa, "Esleitu detektado\n%s\n", agindua_arg_formatuan[1]);
	char *p = agindua_arg_formatuan[1];
	if (p == NULL){
	errorea_tratatu("Ez da ingurune aldagairik ezarri\n");
	}else{
		char *params;
		params = strtok(p, "=");
		char *aldagaia = params;
		params = strtok(NULL, "=");
		char *balioa = params;
	if(setenv(aldagaia, balioa, 1)!=0){

	errorea_tratatu("Ezin izan da env aldagaia gorde\n");
	}
	printf_trace(gurasoa, "Aldagaia: %s=%s", aldagaia,balioa);
	sprintf(prompt, "%s$ ", getenv("GONBIDAPEN"));
	}
	    continue;
    }
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
        pid_finished = waitpid(-1, &status, WNOHANG);    // ume bat bukatu arte zain gelditu
        if ( pid_finished != 0)
      // bukatu den prozesua aurretik sortutakoa ez bada
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

