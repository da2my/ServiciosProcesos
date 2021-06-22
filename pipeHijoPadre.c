#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

int main()
{

    //char msg[] = "HOla papi ";
    int fd[2];
    char buffer[30];
    pid_t pid;

    pipe(fd); //se crea el pipe

    pid = fork(); //se crea el proceso hijo

    switch (pid)
    {
    case -1:
        printf("NO SE HA PODIDO CREAR HIJO...");
        exit(-1);
        break;
    case 0: //HIJO
        printf("El HIJO escribe en el pipe...\n");
        write(fd[1], "Hola papi", 10);//strlen(msg)
        break;
    default:        //PADRE
        wait(NULL); //Espera que finalize proceso hijo
        printf("El PADRE lee del pipe...\n");
        read(fd[0], buffer, 10);
        printf("\tMensaje leido: %s\n", buffer);
        break;
    }
}