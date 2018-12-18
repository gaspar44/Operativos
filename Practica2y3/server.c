#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <fcntl.h>

#include "server.h"

// Global variables
defaultPipes defaultpipes;
sem_t clientSemaphore;

int *globalAceptarAccesoServidor;
int *globalSolicitudAccesoServidor;
int **globalListaPipesPeticion;
int **globalListaPipesRespuesta;



void *startService(void *arg){
	int* pointerToactualClientIndex = (int*) arg;
	int actualClientIndex = *pointerToactualClientIndex;
	free(pointerToactualClientIndex);

	int pipeToSendToClient;
	char fileNameToReadReciveFromClient[10];
	char readedByteFromFile;
	int openedFileDescriptorToRead;

	sem_wait(&clientSemaphore);

	while ( (pipeToSendToClient = getClientAvaliablePipeIndex() ) == -1 );

	sem_post(&clientSemaphore);


	write(globalAceptarAccesoServidor[1],&pipeToSendToClient,sizeof(int));
	read(globalListaPipesPeticion[pipeToSendToClient][0],fileNameToReadReciveFromClient,10);

	int bytesToSendToClient = getBytesToRead(fileNameToReadReciveFromClient);
	openedFileDescriptorToRead = open(fileNameToReadReciveFromClient,O_RDONLY);

	write(globalListaPipesRespuesta[pipeToSendToClient][1],&bytesToSendToClient,sizeof(int));


	if (openedFileDescriptorToRead == -1){
		printf("Archivo no encontrado: %s\n",fileNameToReadReciveFromClient);
		exit(1);
	}

	while ( ( read(openedFileDescriptorToRead,&readedByteFromFile,1) ) == 1){
		write(globalListaPipesRespuesta[pipeToSendToClient][1],&readedByteFromFile,1);
	}

	freePipes(pipeToSendToClient);
	close(openedFileDescriptorToRead);

	pthread_exit(0);

}

void startServer(int numberOfClients, int *aceptarAccesoServidor,int *solicitudAccesoServidor,int **listaPipesPeticion,int **listaPipesRespuesta){
	setGlobalPipes(aceptarAccesoServidor,solicitudAccesoServidor,listaPipesPeticion,listaPipesRespuesta);

	// Initialize avaliable pipes for server
	for (int i = 0;  i < 5; i++)
		defaultpipes.pipesLibres[i]= 1;

	sem_init(&clientSemaphore,0,1);
	pthread_t clientThreads[numberOfClients];

	// Start threads
	for (int i = 0; i < numberOfClients;i++){
		int *indexToSendToTrhead = malloc(sizeof(int));
		*indexToSendToTrhead = i;
		pthread_create(&clientThreads[i],NULL,startService,indexToSendToTrhead);
	}

	// Wait for threads
	for (int i = 0; i< numberOfClients;i++){
		pthread_join(clientThreads[i],NULL);
	}

}

void setGlobalPipes(int *aceptarAccesoServidor,int *solicitudAccesoServidor,int **listaPipesPeticion,int **listaPipesRespuesta){
	globalAceptarAccesoServidor=aceptarAccesoServidor;
	globalSolicitudAccesoServidor=solicitudAccesoServidor;
	globalListaPipesPeticion=listaPipesPeticion;
	globalListaPipesRespuesta=listaPipesRespuesta;

	close(globalAceptarAccesoServidor[0]);
	close(globalSolicitudAccesoServidor[1]);

}

int getClientAvaliablePipeIndex(){
	for (int indexToReturn = 0; indexToReturn < 5; indexToReturn++){

		if (defaultpipes.pipesLibres[indexToReturn] == 1){
			defaultpipes.pipesLibres[indexToReturn] = 0;
			return indexToReturn;
		}

	}
	return -1;
}


void freePipes(int pipeToFree){
	defaultpipes.pipesLibres[pipeToFree] = 1;
}

int getBytesToRead(char *fileToRead){
	int openedFile = open(fileToRead,O_RDONLY);
	char byte;
	int numberOfBytes = 0;

	while ( ( read(openedFile,&byte,1) ) == 1){
		numberOfBytes++;
	}

	close(openedFile);
	return numberOfBytes;
}
