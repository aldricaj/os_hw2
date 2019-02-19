#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

const int MAX_BUFFER = 256;
const char* PIPE_NAME = "/tmp/hw2_p3_a";

int getPipeFD() {
	int fd = open(PIPE_NAME, O_RDONLY);
	if (fd == -1) {
		fd = mkfifo(PIPE_NAME, S_IWUSR | S_IRUSR |
	    		S_IRGRP | S_IROTH);	

	}
	return fd;
}

int recieve(int pipeId) {
	char buffer[MAX_BUFFER];
	char stop[] = {'S','T','O','P','\0'};
	read(pipeId, buffer, MAX_BUFFER);
	
	int i = 0;
	int result = 1;
	while (buffer[i] != '\0' && result == 1 && i < 4) {
		if (buffer[i] != stop[i]) {
			result = 0;
		}
		i++;
	}
	
	if (result == 0) printf(buffer);
	return result;
}

void run() {
	printf("Welcome!\n");
	int fd = getPipeFD();
	while (1==1) {
		int response = recieve(fd);
		if (response == 1) {
			break;
		}
		sleep(1);
	}
	close(fd);
	unlink(PIPE_NAME);
}

void main() {
	run();
}
