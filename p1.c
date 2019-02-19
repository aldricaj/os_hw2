
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

void subroutine(char command[], char filePath[]) {
	int fNum = open(filePath, O_RDWR | O_CREAT, S_IRWXU | S_IRWXG| S_IRWXO);
	dup2(fNum, 1);
	
	if(fork != 0) {
		execl(command, command, NULL);
		exit(1);
	}
	else {
		wait(NULL);
	}
	
	close(fNum);

}

int main(int nargs, char* argv[]) {
	if (nargs < 3) {
		printf("Please pass a command and a filename");
	}
	subroutine(argv[1], argv[2]);
}
