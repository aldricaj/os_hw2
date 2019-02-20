/*
	Shared Memory
	
	This module implements a method to use shared memory.
	
	The backing data structure is a block of memory, internally represented as an array of chars
	
	The first element of this array	will represent the index of the array - 2 to start any and all write operations on.

	The second element of this array will represent the index of the array -1 to start any and all read operations on.

	Both will be clocked to MAX_ELEM - 2

*/

#define SM_MAX_ELEM 256
#define SM_RES_BLOC 2
#define SM_MEM_KEY 8080

int getMemSize() {
	return sizeof('a') * SM_MAX_ELEM + SM_RES_BLOC;
}

struct SharedMemBlock {
	char* writeIndex;
	char* readIndex;
	char* start;
	int shmid;
	int len;
};

struct SharedMemBlock createSharedBlock();

void removeShardBlock(struct SharedMemBlock block);

int writeTo(struct SharedMemBlock block, char* data, int dataLen);

int readFrom(struct SharedMemBlock, char* buffer, int buffLen);

void updateBlock(struct SharedMemBlock, int newWrite, int newRead);

int calcNextIndex(int currIndex, int steps);
