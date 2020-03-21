#define _XOPEN_SOURCE 700

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h> 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <errno.h>

#define osAssert(expr,msg){\
    if(!(expr)){\
        perror(msg);\
        exit(EXIT_FAILURE);\
    }\
}while(0)

int main(int argc, char** argv){
    
    osAssert(4==argc,"Args");
    
    int oldUmask = umask(0);
    
    int mode = strtoll(argv[3],NULL,8);
    
    if(!strcmp(argv[1],"-f")){
        int fd = open(argv[2],O_RDWR | O_CREAT | O_EXCL, mode);
        if(errno==EEXIST)
            osAssert(0,"Alredy exists");
        close(fd);
    }
    else if(!strcmp(argv[1],"-d")){
        
        osAssert(-1!=mkdir(argv[2],mode),"Mkdir failed");
        
    }
    else
        osAssert(0,"wrong argument");
    
    umask(oldUmask);
    
    return 0;
}
