#ifndef CLIENT_H_
#define CLIENT_H_
void startClient(char* actualLine,int *aceptarAccesoServidor,int *solicitudAccesoServidor,int **listaPipesPeticion,int **listaPipesRespuesta);
void closeUnnecessaryPipes(int **listaPipesPeticion,int **listaPipesRespuesta,int pipeIDForListaPipe);
void getFileNameOfAnswer(int clientPID,char* fileAnswerToCreate);

#endif /* CLIENT_H_ */
