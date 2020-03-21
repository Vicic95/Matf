#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <time.h>
#define osAssert(expr,msg){\
    if(!(expr)){\
        perror(msg);\
        exit(EXIT_FAILURE);\
    }\
}while(0)
int main(int argc, char** argv) {
	
	time_t now = time(NULL);
	
	struct tm* formattedTime = localtime(&now);
	osAssert(formattedTime != NULL, "localtime failed");
	
	printf("%d\n", formattedTime->tm_yday);
	
	exit(EXIT_SUCCESS);
}
