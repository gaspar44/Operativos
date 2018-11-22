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

#include "master.h"
#include "client.h"

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

	int requestToServerFromProxy[2];
	int responseToProxyFromServer[2];
	int **requestToProxyFromClient = malloc(numberOfClients * sizeof(int*));
	int **responseToClientFromProxy = malloc(numberOfClients * sizeof(int*));

	for (int i = 0; i < numberOfClients; ++i) {
		int *temp = malloc(2*sizeof(int));
		int *temp2 = malloc(2*sizeof(int));
		*(requestToProxyFromClient + i) = temp;
		*(responseToClientFromProxy + i) = temp2;

	}

	if (pipe(requestToServerFromProxy) == -1 || pipe(responseToProxyFromServer) == -1){
		perror("Error to create pipes");
		exit(1);
	}


	for (int i = 0 ; i < numberOfClients; i ++) {
		if (pipe(requestToProxyFromClient[i]) == -1 || pipe(responseToClientFromProxy[i]) == -1){
			perror("Error to create pipes");
			exit(1);
		}

	}


	if ( (serverPID = fork() ) == - 1)
		exit(1);

	else if (serverPID == 0) {
		printf("Soy servidor: %d\n",getpid());
		exit(0);
	}

	else {
		createClients(createdClientsPID,numberOfClients,PID,requestToProxyFromClient,responseToClientFromProxy);

		for (int i = 0; i < numberOfClients; i++) {
			int magia;
			close(requestToProxyFromClient[i][1]);
			read(requestToProxyFromClient[i][0],&magia,sizeof(int));
			printf("Soy cliente por pipe y : %d\n", magia);

		}

		for (int i = 0; i < numberOfClients ;i++)
			waitpid(createdClientsPID[i],&status,0);

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


pid_t* createClients(pid_t* createdClientsPID,int numberOfClients,int PID,int **requestToProxyFromClient, int **responseToClientFromProxy) {
	pid_t idClients;
	FILE* fileToRead= fopen("./listado_html.txt","r");
	char* actualLine = NULL;
	size_t lineSize = 0;
	ssize_t charsInTheLine;

	if (fileToRead == NULL)
		exit(1);

	for (int i = 0; i < numberOfClients;i++){
		if (PID == getpid()) {
			getline(&actualLine,&lineSize,fileToRead);

			if (( idClients = fork() ) == -1)
				exit(1);

			else if( idClients == 0){
				startClient(actualLine,requestToProxyFromClient[i],responseToClientFromProxy[i]);
				exit(0);
			}

			else
				createdClientsPID[i] = idClients;
		}
	}

	return createdClientsPID;
}
