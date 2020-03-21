#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include <errno.h>
#include <signal.h>

#define osAssert(expr,msg){\
    if(!(expr)){\
        perror(msg);\
        exit(EXIT_FAILURE);\
    }\
}while(0)
               
int sigusr1Count = 0;
int sigusr2Count = 0;
bool shouldTerminate = false;
                      
void signalHandler(int signum) {
	
	switch (signum) {
		
		case SIGUSR1:
			sigusr1Count++;
			break;
		case SIGUSR2:
			sigusr2Count++;
			break;
		case SIGTERM:
			shouldTerminate = true;
			break;
		default:
			break;
	}
}

int main(int argc, char** argv) {
	
	osAssert(signal(SIGUSR1, signalHandler) != SIG_ERR, "signal handler setuo failed");
	osAssert(signal(SIGUSR2, signalHandler) != SIG_ERR, "signal handler setuo failed");
	osAssert(signal(SIGTERM, signalHandler) != SIG_ERR, "signal handler setuo failed");
	
	//fprintf(stderr, "PID: %jd\n", (intmax_t)getpid());
	
	do {
		pause();
	} while(!shouldTerminate);
	
	printf("%d %d\n", sigusr1Count, sigusr2Count);
	
	exit(EXIT_SUCCESS);
}
