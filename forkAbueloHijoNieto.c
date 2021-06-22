#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void main()
{
    pid_t pid, Hijo_pid, pid2, Hijo2_pid;

    pid = fork(); //Soy el abuelo, creo a Hijo

    if (pid == -1)//Ha ocurrido un error
    {
        printf("No se ha podido crear el proceso hijo...");
        exit(-1);
    }
    if(pid==0)
    {
        pid2 = fork();//Soy el hijo, creo a Nietos
        switch (pid2)
        {
        case -1://error
            printf("No se ha podido crear el proceso hijo en el HIJO...");
            exit(-1);
            break;
        case 0://proceso hijo
            printf("\t\tSoy el proceso NIETO %d; Mi padre es = %d \n", getpid(), getppid());
            break;
        default:
            Hijo2_pid = wait(NULL);
            printf("\tSoy el proceso HIJO %d, Mi padre es: %d.\n", getpid(), getppid());
            printf("\tMi hijo: %d termino.\n", Hijo2_pid);
        }
    }
    else
    {
        Hijo_pid = wait(NULL);
        printf("Soy el proceso ABUELO: %d, Mi HIJO: %d termino.\n", getpid(), pid);
    }
    exit(0);
}
