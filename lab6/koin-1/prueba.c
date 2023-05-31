#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork(); // Creamos un proceso hijo
    
    if (pid == 0) {
        // Estamos en el proceso hijo
        sleep(2); // Simulamos una tarea que toma tiempo en el proceso hijo
        printf("Proceso hijo terminado.\n");
    } else if (pid > 0) {
        // Estamos en el proceso padre
        int status;
        // Esperamos al proceso hijo sin bloquear
        while (waitpid(pid, &status, WNOHANG) == 0) {
            printf("Proceso padre: Esperando al hijo...\n");
            sleep(1);
        }
        
        if (WIFEXITED(status)) {
            printf("Proceso hijo terminado correctamente.\n");
        } else {
            printf("Proceso hijo terminado con error.\n");
        }
        
        printf("Continuando en el proceso padre.\n");
    } else {
        // Error al crear el proceso hijo
        perror("fork");
        return 1;
    }

    return 0;
}

