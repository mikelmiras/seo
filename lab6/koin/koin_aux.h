#ifndef koin_aux
#define koin_aux  

#include <unistd.h>

// Erabiltzen diren funtzioen erazagupen aurreratua
// irakurri hurrengo agindua, karaktere kopurua itzuliz
extern ssize_t irakurri_agindua(char *prompt, char *agindua); 
/* string formatuan dauden argumentuak arg[],argc formatuan egituratzeko  */
extern int eskuratu_argumentuak(char *agindua_string, char *arg_array[]);
// debug mezuak erakusteko
extern void printf_trace (bool umea, const char * format, ... );
// errore mezua erakutsi eta atera
extern void errorea_tratatu ( const char * format, ... );

#endif  
