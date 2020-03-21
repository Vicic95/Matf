
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

int main(int argc, char **argv) {
    osAssert(2==argc, "Args");
    
    struct stat podaci;
    osAssert(-1 != stat(argv[1],&podaci), "Stat failed");
    
    int grMask = 070;
    int othMask = 07;
    int ownMask = 0700;
    
    int gr = podaci.st_mode & grMask;
    int oth = podaci.st_mode & othMask;
    int mode = podaci.st_mode & ownMask;
    
    mode |= (gr>>3);
    mode |= (oth<<3);
    
    osAssert(-1!= chmod(argv[1],mode), "Chmod failed");
    
    return 0;
}


