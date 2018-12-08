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

void closeUnnecessaryPipes(int **listaPipesPeticion,int **listaPipesRespuesta,int pipeIDForListaPipe){
	close(listaPipesPeticion[pipeIDForListaPipe][0]);
	close(listaPipesRespuesta[pipeIDForListaPipe][1]);
}

void getFileNameOfAnswer(int clientPID,char* fileAnswerToCreate){
	char stringedClientPID[4];
	strcpy(fileAnswerToCreate,"salida_pid_");
	sprintf(stringedClientPID,"%d",clientPID);
	strcat(fileAnswerToCreate,stringedClientPID);
	strcat(fileAnswerToCreate,"_cliente.html");

}

void startClient(char* actualLine,int *aceptarAccesoServidor,int *solicitudAccesoServidor,int **listaPipesPeticion,int **listaPipesRespuesta){
	close(aceptarAccesoServidor[1]);
	close(solicitudAccesoServidor[0]);
	int clientPID = getpid();
	int pipeIDForListaPipe;

	char* serverAnswerByByte = NULL;
	char* serverAnswer = NULL;
	char *fileAnswer = calloc(100,1);
	getFileNameOfAnswer(clientPID,fileAnswer);

	printf("%s\n",actualLine);
	printf("archivo de salida es: %s\n",fileAnswer);

	if (write(solicitudAccesoServidor[1],&clientPID,sizeof(int)) <= 0)
		perror("Error to write to pipe");

	read(aceptarAccesoServidor[0],&pipeIDForListaPipe,sizeof(int));
	printf("leído: %d\n ",pipeIDForListaPipe);
	closeUnnecessaryPipes(listaPipesPeticion,listaPipesRespuesta,pipeIDForListaPipe);

	write(listaPipesPeticion[pipeIDForListaPipe][1],actualLine,strlen(actualLine));

	while ( read(listaPipesRespuesta[pipeIDForListaPipe][0],serverAnswerByByte,1) > 0 ) {
		strcpy(serverAnswer,serverAnswerByByte);
	}
	printf("hello: %s\n",serverAnswer);

}
