#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "shared_mem.h"


const int MAX_FILE_BUFFER = 256;

int upper(char* textBuffer) {
	int i = 0;
	while (textBuffer[i] != '\0') {
		char c = textBuffer[i];
		if (c >= 'a' && c <= 'z') {
			textBuffer[i] = c - ('a' - 'A');
		}
		i++;
	}
	return i;
}

void sendToServer(struct SharedMemBlock b, char* message) {
	
	int len = upper(message);
	


	printf("Sending Msg: %s\n", message);
	while (writeTo(b, message, len) != 1) {
		sleep(1);
	}
}

void run(char* fileName) {
	FILE* fd = fopen(fileName, "r");
	
	struct SharedMemBlock b = createSharedBlock();

	char lineBuffer[MAX_FILE_BUFFER];
	while(fgets(lineBuffer, MAX_FILE_BUFFER, fd) != NULL) {
		sendToServer(b, lineBuffer);
		sleep(1);	
	}
	char stop[] = {'s','t','o','p','\0'};
	sendToServer(b, stop);
	detach(b);
	fclose(fd);
}

void main(char* args[], int nargs) {
	printf("Welcome\n");
	if (nargs < 2)
		run("test.txt");
	else
		run(args[1]);
}
