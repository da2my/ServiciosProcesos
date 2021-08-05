#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/*-------------------------*/
/*gestion de señales en proceso padre*/
void gestion_padre(int segnal)
{
    printf("Padre recibe señal..%d\n", segnal);
}

/*gestion de señal en proceso hijo*/
void gestion_hijo(int segnal)
{
    printf("Hijo recibe señal..%d\n", segnal);
}
/*-------------------------*/

int main()
{
    int pid_hijo, pid_padre;
    pid_padre = getpid();
    pid_hijo = fork(); //se crea el hijo

    switch (pid_hijo)
    {
    case -1:
        printf("Error al crear el proceso hijo...\n");
        exit(-1);
    case 0:                            //HIJO
                                       /*Tratamiento de la señal en proceso hijo*/
        signal(SIGUSR1, gestion_hijo); //MANEJADOR DE SEÑAL EN HIJO
        while (1)                      //bucle infinito
        {
            sleep(1);
            kill(pid_padre, SIGUSR1); //ENVIA MENSAJE AL PADRE
            pause();                  //hijo espera hasta que llegue señal de respuesta
        };
        break;
    default: //PADRE
             //Tratamiento de la señal en proceso padre
        signal(SIGUSR1, gestion_padre);
        while (1)
        {
            pause(); //padre espera hasta recibir una señal del hijo
            sleep(2);
            kill(pid_hijo, SIGUSR1); //ENVIA SEÑAL AL HIJO
        }

        break;
    }
    return 0;
}