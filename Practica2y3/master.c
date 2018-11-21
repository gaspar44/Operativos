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

	// Se declaran los pipes a utilizar para emular comunicación cliente -> proxy -> server
	int requestToProxy[numberOfClients][2];
	int requestToServer[numberOfClients][2];
	int responseToProxy[numberOfClients][2];
	int responseToClient[numberOfClients][2];


	// Creación de los pipes
	for (int i = 0 ; i < numberOfClients; i ++) {
		pipe(requestToProxy[i]);
		pipe(requestToServer[i]);
		pipe(responseToProxy[i]);
		pipe(responseToClient[i]);
	}


	if ( (serverPID = fork() ) == - 1)
		exit(1);

	else if (serverPID == 0) {
		printf("Soy servidor: %d\n",getpid());
		exit(0);
	}

	else {
		createClients(createdClientsPID,numberOfClients,PID,requestToProxy,requestToServer,responseToProxy,responseToClient);

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


pid_t* createClients(pid_t* createdClientsPID,int numberOfClients,int PID,int requestToProxy[][2], int requestToServer[][2], int responseToProxy[][2], int responseToClient[][2] ){
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
				//printf("Soy cliente y:%d\n",getpid());
				char mierda[8];

				startClient(actualLine,requestToProxy[i],requestToServer[i],responseToProxy[i],responseToClient[i]);
				close(requestToProxy[i][1]);
				read(requestToProxy[i][0],&mierda,8);
				printf("Soy cliente y :%s\n", mierda);
				exit(0);
			}

			else
				createdClientsPID[i] = idClients;
		}
	}

	return createdClientsPID;
}
