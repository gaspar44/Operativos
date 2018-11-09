/*
 * master.h
 *
 *  Created on: 6 nov. 2018
 */

#ifndef MASTER_H_
#define MASTER_H_
#include <unistd.h>
void init();
int getNumberOfClients(char* fileToRead);
pid_t* createClients(pid_t* createdClientsPID,int numberOfClients,int masterPID);

#endif /* MASTER_H_ */
