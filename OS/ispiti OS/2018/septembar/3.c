#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>
#include <errno.h>
#include <math.h>

#define check_error(expr, userMsg) \
	do { \
		if (!(expr)) {\
			perror(userMsg); \
			exit(EXIT_FAILURE); \
		}\
	} while(0)
	
#define check_terror(expr, userMsg) \
	do { \
		int _expr = expr;\
		if (_expr > 0) {\
			errno = _expr;\
			perror(userMsg); \
			exit(EXIT_FAILURE); \
		}\
	} while(0)

typedef struct {
	int i;
} osThreadArg_t;

int m,n;
double p;
double** matrix;
double globalSum = 0;
pthread_mutex_t gLock = PTHREAD_MUTEX_INITIALIZER;

void ucitaj_matricu(){
	
	int i,j;
	
	scanf("%lf%d%d", &p, &m, &n);
	
	matrix = malloc(sizeof(double*)*m);
	check_error(matrix != NULL, "...");
	
	for (i=0; i<m; i++) {
		
		matrix[i] = malloc(sizeof(double)*n);
		check_error(matrix[i] != NULL, "...");
		
		for (j=0; j<n; j++){
			scanf("%lf", &matrix[i][j]);
		}
	}
}

void obrisi_matricu(){
	
	int i,j;
	
	for (i=0; i<m; i++) {
		free(matrix[i]);
	}
	
	free(matrix);
}

void* threadFunc(void* arg) {
	
	osThreadArg_t* inputArg = (osThreadArg_t*) arg;
	double localSum = 0;
	int i = 0;
	
	for (i = 0; i < n; i++) {
		localSum += pow(fabs(matrix[inputArg->i][i]), p);
	}
	
	check_terror(pthread_mutex_lock(&gLock), "...");
	globalSum += localSum;
	check_terror(pthread_mutex_unlock(&gLock), "...");
	
	return NULL;
}

int main(int argc, char** argv) {
	
	check_error(argc == 1, "...");
	
	ucitaj_matricu();
	
	osThreadArg_t* args = malloc(sizeof(osThreadArg_t)*m);
	check_error(args != NULL, "...");
	pthread_t* tids = malloc(sizeof(pthread_t)*m);
	check_error(tids != NULL, "...");
	int i;
	
	for (i = 0; i < m; i++) {
		
		args[i].i = i;
		check_terror(pthread_create(&tids[i], NULL, threadFunc, &args[i]), "...");
	}
	
	for (i = 0; i < m; i++) {

		check_terror(pthread_join(tids[i], NULL), "...");
	}
	
	printf("%lf\n", pow(globalSum, 1.0/p));
	
	obrisi_matricu();
	free(args);
	free(tids);
	
	exit(EXIT_SUCCESS);
}
