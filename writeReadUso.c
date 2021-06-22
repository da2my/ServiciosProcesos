#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

void main (void){
	char saludos[] = "Un saludo!!!\n";
	char buffer[10];//por que de 10??
	int fd, bytesleidos;

	fd=open("texto.txt", O_WRONLY);//Fichero se abre solo para escribir || Por que open() devuelve lo que devuelve

	if(fd == -1){
		printf("ERROR AL ABRIR EL FICHERO...\n");
		exit(-1);
	}
	printf("Escribo en saludos...\n");
	write(fd, saludos, strlen(saludos));//strlen() devuelve la longuitud en int
	close(fd);//cierro el fichero

	fd=open("texto.txt", O_RDONLY);//El fichero se abre solo para lectura
	printf("Contenido del fichero: \n");

	//leo bytes de uno en uno y lo guardo en buffer
	bytesleidos= read(fd, buffer, O_RDONLY);//AQUI PUEDO PONES EN EL ULTIMO PARAMETRO 1
	while(bytesleidos!=0){
		printf("%s", buffer);//pinto el byte leido
		bytesleidos = read(fd, buffer, O_RDONLY);//leo otro byte || //AQUI PUEDO PONES EN EL ULTIMO PARAMETRO 1
	}
	close(fd);
}
