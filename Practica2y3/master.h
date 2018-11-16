/*
 * master.h
 *
 *  Created on: 6 nov. 2018
 */

#ifndef MASTER_H_
#define MASTER_H_
#include <unistd.h>

typedef struct serverPipes{
	int lista_pipes_libres[5];
	int pipes_libres;
}serverPipes;

void init();
int getNumberOfClients(char* fileToRead);
pid_t* createClients(pid_t* createdClientsPID,int numberOfClients,int masterPID);

#endif /* MASTER_H_ */
