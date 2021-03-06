#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <errno.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <math.h>

#define osAssert(expr,msg){\
    if(!(expr)){\
        perror(msg);\
        exit(EXIT_FAILURE);\
    }\
}while(0)

#define MAX_SIZE 1024		

typedef struct {
	sem_t inDataReady;
	int array[MAX_SIZE];
	int arrayLen;
} osInputData;

void* osGetMemoryBlock(const char* path, int* size);

int count_ones(int x);

int main(int argc, char** argv) {
	
	osAssert(argc == 2, "Args");
	
	int size = 0;
	osInputData* block = osGetMemoryBlock(argv[1], &size);
	
	osAssert(sem_wait(&(block->inDataReady)) != -1, "sem wait failed");
	
	int i;
	for (i = 0; i < block->arrayLen; i++) {
		if (count_ones(block->array[i]) >= 4) {
			printf("%d ", block->array[i]);
		}
	}
	printf("\n");
	
	osAssert(munmap(block, size) != -1, "munmap failed");
	
	exit(EXIT_SUCCESS);
}

int count_ones(int x) {
	
	unsigned mask = 1 << (sizeof(int)*8 - 1);
	int count = 0;
	
	while (mask) {
		
		if (x & mask)
			count++;
			
		mask >>= 1;
	}
	
	return count;
	
}

void* osGetMemoryBlock(const char* path, int* size) {
	
	int memFd = shm_open(path, O_RDWR, 0600);
	osAssert(memFd != -1, "shmopen failed");
	
	struct stat fInfo;
	osAssert(fstat(memFd, &fInfo) != -1, "stat failed");
	*size = fInfo.st_size;
	
	void* addr;
	
	osAssert((addr = mmap(0, *size, PROT_READ | PROT_WRITE, MAP_SHARED, memFd, 0)) != MAP_FAILED, "mmap failed");
	
	return addr;
}
