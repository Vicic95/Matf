#define _XOPEN_SOURCE 700

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

 

#define osAssert(expr,msg){\
    if(!(expr)){\
        perror(msg);\
        exit(EXIT_FAILURE);\
    }\
}while(0)

int main(int argc, char** argv){
    
    osAssert(2==argc,"Args");
    
    struct stat finfo;
    
    osAssert(-1!=lstat(argv[1],&finfo),"Stat failed");
    
    if(S_ISREG(finfo.st_mode)){
        printf("%ld\n",(finfo.st_atime - finfo.st_mtime)/(24*60*60));
    }
    else
        osAssert(0,"Not regular");
    
    return 0;
}
