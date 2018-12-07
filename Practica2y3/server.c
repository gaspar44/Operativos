#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#include "server.h"

defaultPipes defaultpipes;
sem_t clientSemaphore;

int *globalAceptarAccesoServidor;
int *globalSolicitudAccesoServidor;
int **globalListaPipesPeticion;
int **globalListaPipesRespuesta;

int getClientPipeIndex(){
	for (int indexToReturn = 0; indexToReturn < 5; indexToReturn++){

		if (defaultpipes.pipesLibres[indexToReturn] == 1){
			defaultpipes.pipesLibres[indexToReturn] = 0;
			return indexToReturn;
		}

	}
	return -1;
}

void *startService(void *arg){
	int* pointerToactualClientIndex = (int*) arg;
	int actualClientIndex = *pointerToactualClientIndex;
	free(pointerToactualClientIndex);
	int pipeToSendToClient;

	sem_wait(&clientSemaphore);

	while ( (pipeToSendToClient = getClientPipeIndex() ) == -1 ){}

	sem_post(&clientSemaphore);


	write(globalAceptarAccesoServidor[1],&pipeToSendToClient,sizeof(int));
	printf("mi actualClientIndex es: %d y el pipe es: %d\n",actualClientIndex,pipeToSendToClient);

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
