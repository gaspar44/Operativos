/*
 * client.c
 *
 *  Created on: 9 nov. 2018
 */
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "client.h"

void startClient(char* actualLine,int requestToProxy[2], int requestToServer[2], int responseToProxy[2], int responseToClient[2]){
	char pipeToCreate[15];
	char clientPID[8];
	sprintf(clientPID,"%d",getpid());
	strcpy(pipeToCreate,actualLine);
	strtok(pipeToCreate,"\r\n");
	strcat(pipeToCreate,".txt");

	if (close(requestToProxy[0]) == -1)
		printf("mierda %d\n",getpid());


	/*int openedPipe = open(pipeToCreate,O_WRONLY|O_CREAT,0666);

	if (openedPipe != -1)
		write(openedPipe,clientPID,strlen(clientPID));*/

	write(requestToProxy[1],clientPID,strlen(clientPID));

	//close(openedPipe);
}
