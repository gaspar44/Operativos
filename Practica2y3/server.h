#ifndef SERVER_H_
#define SERVER_H_
typedef struct defaultPipes{
	int pipesLibres[5];

} defaultPipes;
void startServer(int numberOfClients, int *aceptarAccesoServidor,int *solicitudAccesoServidor,int **listaPipesPeticion,int **listaPipesRespuesta);

#endif /* SERVER_H_ */
