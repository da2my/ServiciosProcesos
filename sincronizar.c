#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/*-------------------------*/
/*gestion de señales en proceso HIJO*/
void manejador(int segnal)
{
    printf("Hijo recibe señal..%d\n", segnal);
}
/*-------------------------*/

int main()
{
    pid_t pidActual;//prueba para ver q es otro proceso y entra al switch
    int pid_hijo;
    pid_hijo = fork(); //creamos hijo
    pidActual = getpid();//prueba para ver q es otro proceso y entra al switch

    switch (pid_hijo)
    {
    case -1:
        printf("Error al crear el proceso hijo...\n");
        exit(-1);
    case 0: //HIJO
        printf("PID actual: %d\n", pidActual);
        signal(SIGUSR1, manejador); //MANEJADOR DE SEÑAL EN HIJO
        while (1)
        {
        };
        break;
    default:                     //PADRE envia 2 señales
        sleep(5);                //segundos
        kill(pid_hijo, SIGUSR1); //ENVIA SEÑAL AL HIJO
        sleep(3);
        kill(pid_hijo, SIGUSR1); //ENVIAR SEÑAL AL HIJO
        sleep(1);
        break;
    }
    return 0;
}