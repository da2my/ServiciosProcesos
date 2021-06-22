#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

int main(void)
{
    int fd[2];
    pid_t pid;
    char saludoPadre[] = "Buenos dias hijo. \0";
    char buffer[80];

    pipe(fd);     //creo pipe
    pid = fork(); //creo proceso

    switch (pid)
    {
    case -1:
        printf("NO SE HA PODIDO CREAR HIJO...");
        exit(-1);
        break;
    case 0:                                  //HIJO RECIBE
        close(fd[1]);                        //cierre el manupulador de entrada
        read(fd[0], buffer, sizeof(buffer)); //leo el pipe || sizeof(buffer)?????Devuelve el numero en bytes de lo que recibe por parametro?????
        printf("\tEl  HIJO recibe algo del pipe: %s\n", buffer);
        break;
    default: //PADRE ENVIA
        close(fd[0]);
        write(fd[1], saludoPadre, strlen(saludoPadre));
        printf("EL PADRE ENVIA MENSAJE AL HIJO...\n");
        wait(NULL); //espero al proceso hijo
        break;
    }

    return 0;
}