#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void main()
{
    pid_t pid, Hijo_pid;
    pid = fork();

    if (pid == -1) //ha ocurrido un error
    {
        printf("No se ha podido crear el proceso hijo...");
        exit(-1);
    }
    if (pid == 0) //Nos encontramos en Proceso hijo
    {
        printf("Soy el proceso hijo \n\t Mi PID es %d, El PID de mi padre es: %d.\n", getpid(), getppid());
    }
    else //Nos encontramos en proceso padre
    {
        Hijo_pid = wait(NULL); //espera la finalizacion del proceso hijo
        printf("Soy el proceso padre:\n\t Mi PID es %d, El PID de mi padre es: %d.\n\t Mi hijo: %d termino.\n", getpid(), getppid(), pid);
    }
    exit(0);
}
