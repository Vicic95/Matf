#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <errno.h>

#include <sys/wait.h>
#include <pthread.h>

#define osAssert(expr,msg){\
    if(!(expr)){\
        perror(msg);\
        exit(EXIT_FAILURE);\
    }\
}while(0)

#define osCheckPthread(pthreadErr, userMsg) \
    do { \
      int __pthreadErr = (pthreadErr); \
      if (__pthreadErr) { \
        errno = __pthreadErr; \
        osAssert(false, userMsg); \
      } \
    } while (0)
    
typedef struct {	
	int tid;
	int row;
} osThreadFuncArgumentType;

void* osThreadFunc(void* arg);

double globalMin = 0;
pthread_mutex_t globalLock;

int N = 0;
int M = 0;
double** matrix;

int main(int argc, char** argv) {
	
	osAssert(argc == 2, "Args");
	
	FILE* f = fopen(argv[1],"r");
	osAssert(f != NULL, "file open failed");
	
	fscanf(f, "%d%d", &N, &M);
	
	int i = 0, j = 0;
	matrix = malloc(N * sizeof(double*));
	osAssert(matrix != NULL, "allocation failed");
	for (i = 0; i < N; i++) {
		matrix[i] = malloc(M*sizeof(double));
		osAssert(matrix[i] != NULL, "allocation failed");
	}
	
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++){
			fscanf(f, "%lf", &matrix[i][j]);
		}
	}
	
	fclose(f);
	
	pthread_t* tids = malloc(N*sizeof(pthread_t));
	osAssert(tids != NULL, "tids allocation failed");
	osThreadFuncArgumentType *args = malloc(N*sizeof(osThreadFuncArgumentType));
	osAssert(args != NULL, "args allocation failed");
	
	osCheckPthread(pthread_mutex_init(&globalLock, NULL), "mutex init failed");
	
	for (i = 0; i < N; i++) {
		args[i].tid = (i+1);
		args[i].row = i;
		osCheckPthread(pthread_create(&tids[i], NULL, osThreadFunc, (void*)&args[i]), "Thread creation failed");
	}
	
	for (i = 0; i < N; i++) {
		
		osCheckPthread(pthread_join(tids[i], NULL), "Thread joining failed");
	}
	
	osCheckPthread(pthread_mutex_destroy(&globalLock), "mutex lock destroy failed");
	
	printf("%lf\n", globalMin);
	
	for (i = 0; i < N; i++)
		free(matrix[i]);
		
	free(matrix);
	free(tids);
	free(args);
	
	exit(EXIT_SUCCESS);
}
void* osThreadFunc(void* arg) {
	
	osThreadFuncArgumentType* args = (osThreadFuncArgumentType*) arg;
	
	double min = matrix[args->row][0];
	int i = 0;
	
	for (i = 1; i < M; i++) {
		
		if (matrix[args->row][i] < min)
			min = matrix[args->row][i];
	}
	
	osCheckPthread(pthread_mutex_lock(&globalLock), "mutex lock failed");
	if (min < globalMin)
		globalMin = min;
	osCheckPthread(pthread_mutex_unlock(&globalLock),"mutex unlock failed");
	
	return NULL;
}
