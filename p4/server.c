#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "shared_mem.h"
#include <string.h>
const int MAX_BUFFER = 256;

int recieve(struct SharedMemBlock b) {
	char buffer[MAX_BUFFER];
	char stop[] = {'S','T','O','P','\0'};

	while (readFrom(b, buffer, MAX_BUFFER) < 0) {
		sleep(1);
	}
	
	int i = 0;
	int result = 1;
	while (buffer[i] != '\0' && result == 1 && i < 4) {
		if (buffer[i] != stop[i]) {
			result = 0;
		}
		i++;
	}
	
	if (result == 0) printf("%s",buffer);
	memset(buffer, 0, MAX_BUFFER);
	return result;
}

void run() {
	printf("Welcome!\n");
	struct SharedMemBlock b = createSharedBlock();
	while (1==1) {
		int response = recieve(b);
		if (response == 1) {
			break;
		}
		sleep(1);
	}
	removeShardBlock(b);
}

void main() {
	run();
}
