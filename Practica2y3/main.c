/*
 * main.c
 *
 *  Created on: 6 nov. 2018
 */

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "master.h"

int main(int argc, char **argv) {
	pid_t master;
	int status = 0;

	if ((master = fork()) == -1 )
		exit(1);

	else if (master == 0)
		init();

	else
		master = wait(&status);

	return 0;

}

