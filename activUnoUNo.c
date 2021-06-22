#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void main(){
	pid_t pid, Hijo_pid;
    pid = fork();
	int var = 6;


	if (pid == -1) //ha ocurrido un error
    {
        printf("No se ha podido crear el proceso hijo...");
        exit(-1);
    }
    if (pid == 0) //Nos encontramos en Proceso hijo
    {
    
    printf("Valor inicial de la variable: %d", var);
			int varH = var-5;
		printf("\nSoy el proceso hijo \n\t Mi PID es %d", getpid());
		printf("\nValor en el Proceso Hijo: %d", varH);
	}
    else //Nos encontramos en proceso padre
    {
        Hijo_pid = wait(NULL); //espera la finalizacion del proceso hijo
		int varP=var+5;
        printf("\nSoy el proceso padre:\n\t Mi PID es %d", getpid());
		printf("\nValor en el Proceso Padre: %d", varP);
    }
    exit(0);

}
