#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include <errno.h>


#define osAssert(expr,msg){\
    if(!(expr)){\
        perror(msg);\
        exit(EXIT_FAILURE);\
    }\
}while(0)

int main(int argc, char** argv) {
	
	osAssert(argc == 4, "Args");
    
	int fd = open(argv[1], O_RDWR);
	osAssert(fd != -1, "open failed");
	
    int a = atoi(argv[2]);
	int b = atoi(argv[3]);

	struct flock fLock;
	fLock.l_type = F_WRLCK;
	fLock.l_whence = SEEK_SET;
	fLock.l_start = a;
	fLock.l_len = b;
	
	osAssert(fcntl(fd, F_GETLK, &fLock) != -1, "flock failed");
	if (fLock.l_type == F_UNLCK)
        printf("unlocked\n");
    else if (fLock.l_type == F_WRLCK)
        printf("exclusive lock\n");
    else 
        printf("shared lock\n");
	
	close(fd);
	
	exit(EXIT_SUCCESS);
}
