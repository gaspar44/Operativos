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

void startClient(char* actualLine,int *requestToProxyFromClient, int *responseToClientFromProxy){
	close(requestToProxyFromClient[0]);
	close(responseToClientFromProxy[1]);
	int clientPID = getpid();

	if (write(requestToProxyFromClient[1],&clientPID,sizeof(int)) <= 0)
		perror("no salió bien");
}
