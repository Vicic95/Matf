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
#include <math.h>


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

double minD = 0;
int initializedD = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
	double x;
	double y;
} Tacka;

typedef struct {
	int idx;
} inputArg;

Tacka* t;
int alocirano = 32;
int zauzeto = 0;

void* prebroj(void* args) {
	
	inputArg* ia = (inputArg*) args;
	double localMin = 0;
	int inicijalizovan = 0;
	int i = 0;
	
	double xf = t[ia->idx].x;
	double yf = t[ia->idx].y;
		
	for (i = 0; i < zauzeto; i++) {
		
		if (i != ia->idx) {
			
			double x = t[i].x;
			double y = t[i].y;
			
			double d = (xf-x)*(xf-x) + (yf-y)*(yf-y);
			
			if (inicijalizovan) {
				if (d < localMin) {
					localMin = d;
				}
			}
			else {
				localMin = d;
				
				inicijalizovan = 1;
			}
		}
	}
	
	pthread_mutex_lock(&lock);
	if (!initializedD) {
		minD= localMin;
		initializedD = 1;
	}
	else {
		if (localMin < minD) {
				minD = localMin;
		}
	}
	pthread_mutex_unlock(&lock);
	
	return NULL;
}

int main(int argc, char** argv) {
	
	osAssert(argc == 1, "Args");

	t = malloc(alocirano*sizeof(Tacka));
	osAssert(t != NULL, "malloc failed");
	double x,y;
	
	while (fscanf(stdin, "%lf%lf", &x, &y) == 2) {
		
		if (zauzeto == alocirano) {
			alocirano *= 2;
			t = realloc(t, alocirano*sizeof(Tacka));
			osAssert(t != NULL, "realloc failed");
		}
		
		t[zauzeto].x = x;
		t[zauzeto].y = y;
		zauzeto++;
	}
	
	pthread_t* tids = malloc(zauzeto*sizeof(pthread_t));
	osAssert(tids != NULL, "malloc failed");
	inputArg* args = malloc(zauzeto*sizeof(inputArg));
	osAssert(args != NULL, "malloc failed");	
	
	int i;
	for (i = 0; i < zauzeto; i++) {
		args[i].idx = i;
		check_thread(pthread_create(&tids[i], NULL, prebroj, &args[i]), "pthread_create failed");
	}
	
	for (i = 0; i < zauzeto; i++)
		check_thread(pthread_join(tids[i], NULL), "join failed");
	
	printf("%lf\n", sqrt(minD));	
	
	free(tids);
	free(args);
	free(t);
	
	exit(EXIT_SUCCESS);
}
