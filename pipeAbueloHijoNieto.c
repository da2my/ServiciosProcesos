#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

void main()
{
    pid_t pid, Hijo_pid, pid2, Hijo2_pid;

    int fd1[2]; //pipe
    int fd2[2]; //pipe

    //Mensajes
    char saludoAbuelo[] = "Saludos del Abuelo.\0";
    char saludoPadre[] = "Saludos del Padre..\0";
    char saludoHijo[] = "Saludos del Hijo...\0";
    char saludoNieto[] = "Saludos del Nieto..\0";

    //Buffer
    char buffer[80] = "";

    pipe(fd1);
    pipe(fd2);
    pid = fork(); //Soy el Abuelo, creo a Hijo

    if (pid == -1) //Ha ocurrido un error
    {
        printf("No se ha podido crear el proceso hijo...");
        exit(-1);
    }

    if (pid == 0) //Nos encontramos en Proceso hijo
    {
        pid2 = fork(); //Soy el hijo, creo a Nieto
        switch (pid2)
        {
        case -1: //Error
            printf("No se ha podido crear el proceso Hijo en el HIJO.");
            break;
        case 0: //Proceso hijo (nieto)
            //NIETO RECIBE
            close(fd2[1]);                        //Cierra el manipulador de entrada
            read(fd2[0], buffer, sizeof(buffer)); //leo el pipe
            printf("\t\tNIETO RECIBE mensaje de su padre: %s\n", buffer);

            //NIETO ENVIA
            printf("\t\tNIETO ENVIA MENSAJE a su padre...\n");
            close(fd1[0]);
            write(fd1[1], saludoNieto, strlen(saludoNieto));
            break;
        default: //Proceso padre (hijo)
            //HIJO RECIBE
            close(fd1[1]);                        //cierra el manipulador de entrada
            read(fd1[0], buffer, sizeof(buffer)); //leo el pipe
            printf("\tHIJO recibe mensaje de ABUELO: %s\n", buffer);

            //HIJO ENVIA a su hijo
            close(fd2[0]);
            write(fd2[1], saludoPadre, strlen(saludoPadre));
            Hijo2_pid = wait(NULL); //espero al hijo

            //RECIBE de su hijo
            close(fd1[1]);
            read(fd1[0], buffer, sizeof(buffer)); //leo el pipe
            printf("\tHIJO RECIBE mensaje de su hijo: %s\n", buffer);

            //HIJO ENVIA  a su PADRE
            printf("\tHIJO ENVIA MENSAJE a su padre...\n", buffer);
            close(fd2[0]);
            write(fd2[1], saludoHijo, strlen(saludoHijo));
            // break;
        }
    }
    else //Nos encontramos en Proceso padre(abuelo)
    {
        //PADRE ENVIA
        printf("ABUELO ENVIA MENSAJE AL HIJO...\n");
        close(fd1[0]);
        write(fd1[1], saludoAbuelo, strlen(saludoAbuelo)); //escribo
        Hijo_pid = wait(NULL);                             //espera la finalizacion del hijo

        //PADRE RECIBE
        close(fd2[1]);
        read(fd2[0], buffer, sizeof(buffer)); //leo pipe
        printf("EL ABUELO RECIBE MENSAJE del HIJO: %s\n", buffer);
    }
    exit(0);
}