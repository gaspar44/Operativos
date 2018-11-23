#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "server.h"

defaultPipes defaultpipes;
sem_t semaforo1;
int contThread = 0;
void* threadCreation(void *arg){
	sem_wait(&semaforo1);
	contThread = contThread + 1;
	sem_post(&semaforo1);

	pthread_exit(0);
}

void startServer(int numberOfClients, int *aceptarAccesoServidor,int *solicitudAccesoServidor,int **listaPipesPeticion,int **listaPipesRespuesta){
	close(aceptarAccesoServidor[0]);
	close(solicitudAccesoServidor[1]);

	for (int i = 0;  i < 5; i++)
		defaultpipes.pipesLibres[i]= 1;

	sem_init(&semaforo1,0,1);
	pthread_t clientThreads[numberOfClients];

	for (int i = 0; i< numberOfClients;i++){
		pthread_create(&clientThreads[i],NULL,threadCreation,NULL);

	}

	for (int i = 0; i< numberOfClients;i++){
		pthread_join(clientThreads[i],NULL);
	}

	printf("finalizado: %d\n", contThread);
}
