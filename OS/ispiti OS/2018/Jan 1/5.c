#define _XOPEN_SOURCE 700
#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <string.h>
#include <ctype.h>

#include <semaphore.h>
#include <sys/mman.h>
#include <errno.h>


#define osAssert(expr,msg){\
    if(!(expr)){\
        perror(msg);\
        exit(EXIT_FAILURE);\
    }\
}while(0)

	
#define ARRAY_MAX (1024)
	
typedef struct {
	sem_t inData;
	sem_t outData;
	char str[ARRAY_MAX];
} mBlock;

void* getMemoryBlock(char* path, int* blockSize) {
	
	int memFd = shm_open(path, O_RDWR, 0);
	osAssert(memFd != -1, "shm_open failed");
	
	struct stat fInfo;
	osAssert(fstat(memFd, &fInfo) != -1, "fstat failed");
	*blockSize = fInfo.st_size;
	
	void* addr;
	osAssert((addr = mmap(NULL, *blockSize, PROT_READ|PROT_WRITE, MAP_SHARED, memFd, 0)) != MAP_FAILED, "mmap failed");
	
	close(memFd);
	
	return addr;
}

int main(int argc, char** argv) {
	
    for (int i = 1; i < argc; i++)
        fprintf(stderr, "%s\n", argv[i]);
    
	osAssert(argc == 2, "Args");
	
	int size = 0;
	mBlock* blk = getMemoryBlock(argv[1], &size);
	
	osAssert(sem_wait(&(blk->inData)) != -1, "sem_wait failed");
	
	int i = 0;
	for (i = 0; blk->str[i] != 0; i++) {
		if (islower(blk->str[i]))
			blk->str[i] = toupper(blk->str[i]);
		else if (isupper(blk->str[i]))
			blk->str[i] = tolower(blk->str[i]);
	}
	fprintf(stderr, "Result: %s\n", blk->str);
	osAssert(sem_post(&(blk->outData)) != -1, "sem_post failed");
	
	osAssert(munmap(blk, size) != -1, "munmap failed");
		 
	exit(0);
}
