#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#include "server.h"

defaultPipes defaultpipes;
sem_t clientSemaphore;
int contThread = 0;

/*void* threadCreation(void *arg){
	sem_wait(&semaforo1);
	contThread = contThread + 1;
	sem_post(&semaforo1);

	pthread_exit(0);
}*/

int getClientPipeIndex(){

}

void *startService(void *arg){


}

void startServer(int numberOfClients, int *aceptarAccesoServidor,int *solicitudAccesoServidor,int **listaPipesPeticion,int **listaPipesRespuesta){
	close(aceptarAccesoServidor[0]);
	close(solicitudAccesoServidor[1]);

	for (int i = 0;  i < 5; i++)
		defaultpipes.pipesLibres[i]= 1;

	sem_init(&clientSemaphore,0,1);
	pthread_t clientThreads[numberOfClients];

	int *i = malloc(sizeof(int));
	*i = 0;

	while (*i != numberOfClients){
		pthread_create(&clientThreads[*i],NULL,startService,i);
		(*i)++;
	}
	free(i);


	for (int i = 0; i< numberOfClients;i++){
		pthread_join(clientThreads[i],NULL);
	}

}
