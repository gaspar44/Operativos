/*
 * master.c
 *
 *  Created on: 6 nov. 2018
 *      Author: gaspar
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "master.h"

void init() {
	int PID = getpid();
	int serverPID;
	int numberOfClients = getNumberOfClients("./listado_html.txt");
	int status;
	pid_t createdClientsPID[numberOfClients];
	pid_t idClients;

	if ( (serverPID = fork() ) == - 1)
		exit(1);

	else if (serverPID == 0) {
		printf("Soy servidor: %d\n",getpid());
		exit(0);
	}

	else {

		for (int i = 0; i < numberOfClients;i++){
			if (PID == getpid()) {
				idClients = fork();

				if (idClients == -1)
					exit(1);

				else if( idClients == 0){
					printf("Soy cliente y:%d\n",getpid());
					exit(0);
				}

				else
					createdClientsPID[i] = idClients;
			}
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
