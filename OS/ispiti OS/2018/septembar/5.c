#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <semaphore.h>
#include <signal.h>
#include <sys/mman.h>

#define check_error(expr, userMsg) \
	do { \
		if (!(expr)) {\
			perror(userMsg); \
			exit(EXIT_FAILURE); \
		}\
	} while(0)

#define ARRAY_MAX (1024)	

typedef struct {
	sem_t done;
	int array[ARRAY_MAX];
	unsigned n;
} osInputData_t;

int op = 0;

void sigHandler(int signum) {
	
	if (signum == SIGUSR1) {
		op = -1;
	}
	else if (signum == SIGUSR2) {
		op = 2;
	}
}

int main(int argc, char** argv) {
    check_error(argc == 2, "argc");
	
	int memFd = shm_open(argv[1], O_RDWR, 0600);
	check_error(memFd != -1, "memFd");
	
	struct stat fInfo;
	check_error(fstat(memFd, &fInfo)!=-1, "fstat");
	unsigned size = fInfo.st_size;
	
	void* addr = mmap(0, size, PROT_WRITE|PROT_READ, MAP_SHARED, memFd, 0);
	check_error(addr != MAP_FAILED, "addr != MAP_FAILED");
	
	close(memFd);
	
	osInputData_t* data = (osInputData_t*)addr;
	
	check_error(signal(SIGUSR1, sigHandler) != SIG_ERR, "signal SIGUSR1")	;
	check_error(signal(SIGUSR2, sigHandler) != SIG_ERR, "signal SIGUSR2")	;
	
	pause();
	
	for (int i = 0; i < data->n; i++) {
		data->array[i] *= op;
	}
	
	check_error(sem_post(&(data->done)) != -1, "sem_post");
	
	check_error(munmap(data, size) != -1, "munmap");

	exit(EXIT_SUCCESS);
}
