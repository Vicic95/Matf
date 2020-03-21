#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include <string.h>
#include <errno.h>

#define osAssert(expr,msg){\
    if(!(expr)){\
        perror(msg);\
        exit(EXIT_FAILURE);\
    }\
}while(0)

int main(int argc, char **argv) {
    osAssert(3==argc,"Args");
    
    struct stat finfo;
    osAssert(-1!=lstat(argv[1],&finfo),"Stat failed");
    
    char *absrcPath = realpath(argv[1],NULL);
    char *abdstPath = realpath(argv[2],NULL);
    
    if(absrcPath!= NULL && abdstPath!=NULL && !strcmp(absrcPath,abdstPath)){
        osAssert(0,"Same file");
    }else
        osAssert(-1!=rename(argv[1],argv[2]),"Rename failed");
    free(absrcPath);
    free(abdstPath);
    
    return 0;
}
