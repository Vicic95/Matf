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

char* meseci[12]={"januar", "februar","mart","april","maj","jun","jul","avgust","septembar","oktobar","novembar","decembar"};

int main(int argc, char** argv) {
	
	osAssert(argc == 2, "Args");
	
	time_t sek = (time_t)atol(argv[1]);
	struct tm* vreme = localtime(&sek);
	
	osAssert(vreme!=NULL, "localtime failed");
	
	printf("%s\n", meseci[vreme->tm_mon]);
	
	exit(EXIT_SUCCESS);
}
