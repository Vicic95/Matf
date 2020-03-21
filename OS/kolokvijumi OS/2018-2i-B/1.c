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
    osAssert(2==argc,"Args");
    
    struct stat finfo;
    osAssert(-1!=stat(argv[1],&finfo),"Stat failed");
    
    unsigned sati;
    
    if((finfo.st_atime-finfo.st_mtime)%3600==0)
        sati = (finfo.st_atime-finfo.st_mtime)/3600;
    else
        sati = ((finfo.st_atime-finfo.st_mtime)/3600)+1; 
    printf("%u\n",sati);
    
    return 0;
}
