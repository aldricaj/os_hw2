/*
	Shared Memory
	
	This module implements a method to use shared memory.
	
	The backing data structure is a block of memory, internally represented as an array of chars
	
	The first element of this array	will represent the index of the array - 2 to start any and all write operations on.

	The second element of this array will represent the index of the array -1 to start any and all read operations on.

	Both will be clocked to MAX_ELEM - 2

*/

#include "shared_mem.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

struct SharedMemBlock createSharedBlock() {
	struct SharedMemBlock block;
	printf("Creating memory Block\n");	
	int memId;
	int init = 1; // if init gets turned to 0, initialization steps will not be taken
	if(memId = shmget((key_t) SM_MEM_KEY, getMemSize(), IPC_CREAT | IPC_EXCL | 0666) < 0) {
		switch(errno) {
			case EEXIST:
				printf("Mem Block already exists. No init needed.\n");
				memId = shmget((key_t) SM_MEM_KEY, getMemSize(), 0666);
				init = 0; 
				break;
			default:
				printf("Error in allocating shared memory");
				exit(1);
		}
	}
	
	char* shmStart = shmat(memId, NULL,0);
	if (init == 1) {
		// initialize the memory
		printf("Initializing Shared data block\n");
		shmStart[0] = (char) 0;
		shmStart[1] = (char) 0;
	}

	block.writeIndex = shmStart;
	block.readIndex = shmStart + 1;
	block.shmid = memId;
	block.start = shmStart + 2;
	block.len = SM_MAX_ELEM;
	printf("Block Created\n");
	return block;
}

void detach(struct SharedMemBlock block) {
	shmdt(block.writeIndex);
}

void removeSharedBlock(struct SharedMemBlock block) {
	shmdt(block.writeIndex);
	shmctl(block.shmid, IPC_RMID, NULL);
}


int writeTo(struct SharedMemBlock block, char* data, int dataLen) {
	return 1;
}

int readFrom(struct SharedMemBlock block, char* buffer, int buffLen) {
	return 1;
}

void updateBlock(struct SharedMemBlock block, int newWrite, int newRead) {

}

int calcNextIndex(int currIndex, int steps) {
	return 1;
}

void printBlock(struct SharedMemBlock b) {
	printf("Write: %i\tRead:%i\n", (int) *(b.writeIndex), (int) *(b.readIndex));

	printf("Shared Block\n");
	for (int i = 0; i <= 10 && i < b.len; i++) {
		printf("%i:\t%i\n", i, b.start[i]);
	}
}

void run(int parent) {
	struct SharedMemBlock b = createSharedBlock();
	printBlock(b);
	
	b.readIndex[0] = 1;
	printBlock(b);
	if (parent == 1) { 
		removeSharedBlock(b);
	}

}

void main() {
	if (fork() == 0) {
		printf("Child"); 
		run(0);
	} else {
		sleep(3);
		run(1);
	}
}
