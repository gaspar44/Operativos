#include <stdio.h>
#include <unistd.h>
#include "server.h"


void startServer(int *requestToServerFromProxy,int *responseToProxyFromServer){
	close(requestToServerFromProxy[1]);
	close(responseToProxyFromServer[0]);
}
