#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <errno.h>

#include <pthread.h>
#include <string.h>

#define osAssert(expr,msg){\
    if(!(expr)){\
        perror(msg);\
        exit(EXIT_FAILURE);\
    }\
}while(0)

#define MAX_SIZE (256)

int main(int argc, char** argv) {
	
	osAssert(argc == 3, "Args");
	
	int fd = open(argv[1], O_RDONLY);
	osAssert(fd != -1, "open failed");
	
	FILE* f = fdopen(fd, "r");
	osAssert(f != NULL, "fdopen failed");
	
	int wordLength = strlen(argv[2]);
	
	char localBuffer[MAX_SIZE];
	while (!feof(f)) {
		
		fscanf(f, "%s", localBuffer);
		if (!strcmp(localBuffer, argv[2])) {
			
			struct flock lock;
			lock.l_type = F_WRLCK;
			lock.l_whence = SEEK_SET;
			lock.l_start = ftell(f);
			lock.l_len = -wordLength;
			
			osAssert(fcntl(fd, F_GETLK, &lock) != -1, "fcntl failed");
			
			long currentOffset = ftell(f) - wordLength;
			
			switch (lock.l_type) {
				case F_WRLCK:
					printf("%ld w\n", currentOffset);
					break;
				case F_RDLCK:
					printf("%ld r\n", currentOffset);
					break;
				case F_UNLCK:
					break;
			}
		}
	}
	
	fclose(f);
	
	exit(EXIT_SUCCESS);
}
