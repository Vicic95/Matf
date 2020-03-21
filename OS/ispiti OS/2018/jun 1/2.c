#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>

#define osAssert(expr,msg){\
    if(!(expr)){\
        perror(msg);\
        exit(EXIT_FAILURE);\
    }\
}while(0)

#define check_errorP(expr, userMsg) \
	do {\
		int _err = expr; \
		if (_err > 0) {\
			errno = _err; \
			osAssert(0, userMsg);\
		}\
	} while (0)

int maxC;
int numC;
int initialized;
pthread_mutex_t globalLock = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
	
	char* path;
	char c;
} threadArg_t;

typedef struct {
	
	char c;
	int num;
} threadOutArg_t;

void* threadFunc(void* arg) {
	
	threadArg_t* a = (threadArg_t*)arg;
	char c;
	FILE* f = fopen(a->path, "r");
    if (!f)
    {
        exit(1);
    }
	threadOutArg_t* localCnt = malloc(sizeof(threadOutArg_t));
	osAssert(localCnt != NULL, "...");
	
	localCnt->c = a->c;
	localCnt->num = 0;
	
	while ((c=fgetc(f)) != EOF) {
		
		if (tolower(c) == a->c)
			localCnt->num++;
	}
	
	fclose(f);
	
	check_errorP(pthread_mutex_lock(&globalLock), "...");
	if (initialized) {
		
		if (localCnt->num > numC) {
			
			maxC = localCnt->c;
			numC = localCnt->num;
		}
	}
	else {
		
		maxC = localCnt->c;
		numC = localCnt->num;
		
		initialized = 1;
	}
	check_errorP(pthread_mutex_unlock(&globalLock), "...");
	
	return localCnt;
}

int main(int argc, char** argv) {
	
	osAssert(argc == 2, "Args");
	
	pthread_t* tids = malloc(sizeof(pthread_t)*26);
	osAssert(tids != NULL, "...");
	threadArg_t* args = malloc(sizeof(threadArg_t)*26);
	osAssert(args != NULL, "...");
	
	for (int i = 0; i < 26; i++) {
		
		args[i].c = 'a' + i;
		args[i].path = argv[1];
		check_errorP(pthread_create(&tids[i], NULL, threadFunc, &args[i]), "...");
	}
	
	for (int i = 0; i < 26; i++) {
		
		threadOutArg_t* a = NULL;
		check_errorP(pthread_join(tids[i], (void**)&a), "...");
		printf("%d ", a->num);
		free(a);
	}
	
	printf("\n%c\n", maxC);
	
	free(tids);
	free(args);
	
	exit(EXIT_SUCCESS);
}
