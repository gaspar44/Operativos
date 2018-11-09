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

void startClient(char* actualLine){
	char pipeToCreate[15];
	strcpy(pipeToCreate,actualLine);
	strtok(pipeToCreate,"\r\n");
	strcat(pipeToCreate,".txt");

	int openedPipe = open(pipeToCreate,O_WRONLY|O_CREAT,0666);
	write(openedPipe,pipeToCreate,strlen(pipeToCreate));

	close(openedPipe);
}
