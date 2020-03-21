#define _XOPEN_SOURCE 700

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#include <time.h>

#define osAssert(expr,msg){\
    if(!(expr)){\
        perror(msg);\
        exit(EXIT_FAILURE);\
    }\
}while(0)
		
#define SECS_PER_DAY (24*60*60);	
	
int main(int argc, char** argv) {
	
	osAssert(argc == 2, "Args");
	
	time_t now = time(NULL);
	int daysToAdd = atoi(argv[1]);
	now += daysToAdd*SECS_PER_DAY;
	
	struct tm *formated_time = localtime(&now);
	
	switch (formated_time->tm_wday) {
		case 0:
			printf("Nedelja %d\n",formated_time->tm_mday);
			break;
		case 1:
			printf("Ponedeljak %d\n",formated_time->tm_mday);
			break;
		case 2:
			printf("Utorak %d\n",formated_time->tm_mday);
			break;
		case 3:
			printf("Sreda %d\n",formated_time->tm_mday);
			break;
		case 4:
			printf("Cetvrtak %d\n",formated_time->tm_mday);
			break;
		case 5:
			printf("Petak %d\n",formated_time->tm_mday);
			break;
		case 6:
			printf("Subota %d\n",formated_time->tm_mday);
			break;
		default:
			break;
	}
	
	exit(EXIT_SUCCESS);
}
