#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <time.h>


#define osAssert(expr,msg){\
    if(!(expr)){\
        perror(msg);\
        exit(EXIT_FAILURE);\
    }\
}while(0)

char* week[7] = {"nedelja", "ponedeljak", "utorak", "sreda", "cetvrtak", "petak", "subota"};

int main(int argc, char** argv) {
	osAssert(argc==2, "Args");
	fprintf(stderr, "%s\n", argv[1]);
	int days = atoi(argv[1]);
	
	time_t now = time(NULL);
	now += days*24*60*60;
	struct tm* brokenTime = localtime(&now);
	osAssert(brokenTime != NULL, "...");
	
	printf("%s\n", week[brokenTime->tm_wday]);
	
	exit(EXIT_SUCCESS);
}
