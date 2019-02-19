#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

const int MAX_FILE_BUFFER = 256;
const char* PIPE_NAME = "/tmp/hw2_p3_a";

int getPipeFD() {
	printf("GEtting pipe\n");
	int fd = open(PIPE_NAME, O_WRONLY);
	if (fd == -1) {
		printf("Creating Pipe\n");
		fd = mkfifo(PIPE_NAME, S_IWUSR | S_IRUSR |
	    		S_IRGRP | S_IROTH);	

	}
	return fd;
}

char* upper(char* textBuffer) {
	int i = 0;
	while (textBuffer[i] != '\0') {
		char c = textBuffer[i];
		if (c >= 'a' && c <= 'z') {
			textBuffer[i] = c - ('a' - 'A');
		}
		i++;
	}
	return textBuffer;
}

void sendToServer(int pipeId, char* message) {
	
	upper(message);
	printf("Sending Msg: %s\n", message);
	write(pipeId,message, MAX_FILE_BUFFER);
}

void run(char* fileName) {
	FILE* fd = fopen(fileName, "r");

	char lineBuffer[MAX_FILE_BUFFER];
	int pfd = getPipeFD();
	while(fgets(lineBuffer, MAX_FILE_BUFFER, fd) != NULL) {
		sendToServer(pfd, lineBuffer);
		sleep(1);	
	}
	char stop[] = {'s','t','o','p','\0'};
	sendToServer(pfd, stop);
	close(pfd);
}

void main() {
	printf("Welcome\n");
	run("test.txt");
}
