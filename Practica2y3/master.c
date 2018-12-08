/*
 * master.c
 *
 *  Created on: 6 nov. 2018
 */
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#include "master.h"
#include "client.h"
#include "server.h"

void init() {
	int PID = getpid();
	int serverPID;
	int numberOfClients = getNumberOfClients("./listado_html.txt");
	int status;
	pid_t createdClientsPID[numberOfClients];

	/*
	 * Se declaran los pipes a utilizar para emular comunicación cliente -> proxy -> server
	 * Como la comunicación entre proxy -> master y master -> proxy es de un proceso, sólo es necesario un pipe para leer todo de master y viceversa
	 *
	 *
	 * Estas reservas de memoria dinámica son debido a que es necesario poder guardar cada uno de los pipes que comunicarán cliente con
	 * el master y viceversa por 2 pipes para cada uno de los hijos con master. Para evitar conflictos al momento de pasar argumentos a
	 * las funciones respectivas que leen este código se manejan apuntadores, facilitando su modificación.
	 *
	 */

	int aceptarAccesoServidor[2];
	int solicitudAccesoServidor[2];
	int **listaPipesPeticion = malloc(numberOfClients * sizeof(int*));
	int **listaPipesRespuesta = malloc(numberOfClients * sizeof(int*));

	for (int i = 0; i < numberOfClients; ++i) {
		int *temp = malloc(2*sizeof(int));
		int *temp2 = malloc(2*sizeof(int));
		*(listaPipesPeticion + i) = temp;
		*(listaPipesRespuesta + i) = temp2;

	}

	if (pipe(aceptarAccesoServidor) == -1 || pipe(solicitudAccesoServidor) == -1){
		perror("Error to create pipes");
		exit(1);
	}


	for (int i = 0 ; i < numberOfClients; i ++) {
		if (pipe(listaPipesPeticion[i]) == -1 || pipe(listaPipesRespuesta[i]) == -1){
			perror("Error to create pipes");
			exit(1);
		}
	}

	if ( (serverPID = fork() ) == - 1)
		exit(1);

	else if (serverPID == 0) {
		printf("Servidor creado con PID: %d\n",getpid());
		startServer(numberOfClients,aceptarAccesoServidor,solicitudAccesoServidor,listaPipesPeticion,listaPipesRespuesta);
		printf("Servidor acabado\n");
		exit(0);
	}

	else {
		createClients(createdClientsPID,numberOfClients,PID,aceptarAccesoServidor,solicitudAccesoServidor,
				listaPipesPeticion,listaPipesRespuesta);

		for (int i = 0; i < numberOfClients ;i++){
			waitpid(createdClientsPID[i],&status,0);
			printf("Cliente con PID %d terminado\n",createdClientsPID[i]);
		}

		waitpid(serverPID,&status,0);

	}

}


int getNumberOfClients(char* fileToRead){
	FILE *readedFile = fopen(fileToRead,"r");

	if (readedFile == NULL)
		exit(1);

	int numberOfLines = 0;

		while (!feof(readedFile)){
			if ( fgetc(readedFile) == '\n')
				numberOfLines = numberOfLines + 1;
		}

	fclose(readedFile);
	return numberOfLines;

}


pid_t* createClients(pid_t* createdClientsPID,int numberOfClients,int PID,int *aceptarAccesoServidor,int *solicitudAccesoServidor,
		int **listaPipesPeticion,int **listaPipesRespuesta){
	pid_t idClients;
	FILE* fileToRead= fopen("./listado_html.txt","r");
	char* actualLine = NULL;
	char* readedLine = NULL;
	size_t lineSize = 0;
	ssize_t charsInTheLine;
	int pipeToClient[2];

	if (fileToRead == NULL)
		exit(1);

	for (int i = 0; i < numberOfClients;i++){
		if (PID == getpid()) {
			getline(&readedLine,&lineSize,fileToRead);

			if ( ( pipe(pipeToClient) ) == -1 || ( idClients = fork() ) == -1)
				exit(1);

			else if( idClients == 0){
				printf("Cliente con PID: %d creado\n",getpid());
				close(pipeToClient[1]);
				read(pipeToClient[0],&actualLine,10);
				close(pipeToClient[0]);

				startClient(actualLine,aceptarAccesoServidor, solicitudAccesoServidor,
						listaPipesPeticion,listaPipesRespuesta);
				exit(0);
			}

			else{
				createdClientsPID[i] = idClients;

				close(pipeToClient[0]);
				write(pipeToClient[1],&readedLine,strlen(readedLine));
				close(pipeToClient[1]);
			}

		}
	}

	return createdClientsPID;
}
