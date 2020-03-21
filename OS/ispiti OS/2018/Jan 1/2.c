#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <pthread.h>
#include <errno.h>


#define osAssert(expr,msg){\
    if(!(expr)){\
        perror(msg);\
        exit(EXIT_FAILURE);\
    }\
}while(0)

#define check_thread(expr, msg) \
	do {\
		int t = (expr);\
		if (t){\
			errno = t; \
			osAssert(false, msg); \
		}\
	} while (0)


int globalSum = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

const char* charsToFind;
int n;
int k;
const char* filePath;
typedef struct {
	int idx;
} inputArg;

void* prebroj(void* args) {
	
	inputArg* ia = (inputArg*) args;
	int localSum = 0;
	int fd = open(filePath, O_RDONLY);
	off_t start = ia->idx*(n/k);
	off_t end = (ia->idx+1)*(n/k) - (strlen(charsToFind)+1);
	off_t curr_off = start;
	
	osAssert(fd != -1, "file open failed");
	
	int bufSize = strlen(charsToFind) + 1;
	char* buffer = malloc(bufSize);
	
	while (curr_off <= end) {
		
		osAssert(lseek(fd, curr_off, SEEK_SET) != -1, "lseek failed");
		
		osAssert(read(fd, buffer, bufSize - 1) == (bufSize-1), "read failed");
		
		buffer[bufSize-1] = 0;
		
		if (strcmp(buffer, charsToFind) == 0)
			localSum++;
		
		curr_off += 1;
	}
	
	close(fd);
	free(buffer);
	
	pthread_mutex_lock(&lock);
	globalSum += localSum;
	pthread_mutex_unlock(&lock);
	
	return NULL;
}

int main(int argc, char** argv) {
	
	osAssert(argc == 4, "Args");
	
	filePath = argv[1];
	charsToFind = argv[2];
	k = atoi(argv[3]);
	struct stat fInfo;
	osAssert(stat(argv[1], &fInfo) != -1, "stat failed");
	n = fInfo.st_size;
	
	pthread_t* tids = malloc(k*sizeof(pthread_t));
	osAssert(tids != NULL, "malloc failed");
	inputArg* args = malloc(k*sizeof(inputArg));
	osAssert(args != NULL, "malloc failed");
	
	int i;
	for (i = 0; i < k; i++) {
		args[i].idx = i;
		check_thread(pthread_create(&tids[i], NULL, prebroj, &args[i]), "pthread_create failed");
	}
	
	for (i = 0; i < k; i++)
		check_thread(pthread_join(tids[i], NULL), "join failed");
	
	printf("%d\n", globalSum);	
	
	free(tids);
	free(args);
	
	exit(EXIT_SUCCESS);
}
