/*
 * client.c
 *
 *  Created on: 9 nov. 2018
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include "client.h"

void startClient(char* actualLine,int *aceptarAccesoServidor,int *solicitudAccesoServidor,int **listaPipesPeticion,int **listaPipesRespuesta){
	close(aceptarAccesoServidor[1]);
	close(solicitudAccesoServidor[0]);
	int clientPID = getpid();
	int pipeIDForListaPipe;
	char* serverAnswerByByte = NULL;
	char* serverAnswer = NULL;

	printf("%s\n ",actualLine);

	if (write(solicitudAccesoServidor[1],&clientPID,sizeof(int)) <= 0)
		perror("Error to write to pipe");

	read(aceptarAccesoServidor[0],&pipeIDForListaPipe,sizeof(int));
	printf("leído: %d\n ",pipeIDForListaPipe);
	close(listaPipesPeticion[pipeIDForListaPipe][0]);
	close(listaPipesRespuesta[pipeIDForListaPipe][1]);

	write(listaPipesPeticion[pipeIDForListaPipe][1],actualLine,strlen(actualLine));

	while ( read(listaPipesRespuesta[pipeIDForListaPipe][0],serverAnswerByByte,1) > 0 ) {
		strcpy(serverAnswer,serverAnswerByByte);
	}
	printf("hello: %s\n",serverAnswerByByte);

}
