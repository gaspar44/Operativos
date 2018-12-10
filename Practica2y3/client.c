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
	int bytesToRead;

	char serverAnswerByByte;
	char *fileAnswer = malloc(100*sizeof(char));
	getFileNameOfAnswer(clientPID,fileAnswer);
	FILE* exitFile = fopen(fileAnswer,"w");

	if (write(solicitudAccesoServidor[1],&clientPID,sizeof(int)) <= 0)
		perror("Error to write to pipe");

	read(aceptarAccesoServidor[0],&pipeIDForListaPipe,sizeof(int));
	closeUnnecessaryPipes(listaPipesPeticion,listaPipesRespuesta,pipeIDForListaPipe);

	write(listaPipesPeticion[pipeIDForListaPipe][1],actualLine,strlen(actualLine));
	read(listaPipesRespuesta[pipeIDForListaPipe][0],&bytesToRead,sizeof(int));

	while ( bytesToRead != 0) {
		read(listaPipesRespuesta[pipeIDForListaPipe][0],&serverAnswerByByte,1);
		fprintf(exitFile,"%c",serverAnswerByByte);
		bytesToRead--;
	}

	fclose(exitFile);
	close(listaPipesRespuesta[pipeIDForListaPipe][0]);
	close(listaPipesPeticion[pipeIDForListaPipe][1]);
	close(aceptarAccesoServidor[0]);
	close(solicitudAccesoServidor[1]);
	printf("Archivo salida_pid_%d_cliente.html creado. Favor revisar. Cliente terminando\n",clientPID);

}
