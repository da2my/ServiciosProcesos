#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fp;
    int p, bytesleidos;
    char saludo[] = "Un saludo!!!\n", buffer[10];

    p = mknod("FIFO2", S_IFIFO | 0666, O_RDWR); //permiso de lectura y escritura

    if (p == -1)
    {
        printf("HA OCURRIDO UN ERROR... \n");
        exit(0);
    }
    while (1)
    {
        fp = open("FIFO2", O_RDONLY);
        bytesleidos = read(fp, buffer, 1);
        printf("OBTENIENDO Informacion...");
        while (bytesleidos != 0)
        {
            printf("%s", buffer);
            bytesleidos = read(fp, buffer, 1); //leo otro byte
        }
        close(fp);
    }
    return (0);
}