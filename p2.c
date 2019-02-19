#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

const int BUFF_MAX = 256;

void subroutine() {
	FILE* findPipe = popen("find . -name \"*.c\"", "r");
	char buff[BUFF_MAX];
	
	FILE* trPipe = popen("tr a-z A-Z", "w");
	while (fgets(buff, BUFF_MAX, findPipe) != NULL) {
		int i = 0;
		while (buff[i] != '\0') {
			fputc(buff[i], trPipe);
			i++;
		}
	}

	pclose(trPipe);
	pclose(findPipe);

}

int main(int nargs, char* args[]) {
	subroutine();
}
