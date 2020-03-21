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
    
    osAssert(4==argc,"Args");
    
    struct stat finfo;
    osAssert(-1!=lstat(argv[1],&finfo),"Stat failed");
    
    int offset = atoi(argv[2]);
    int duzina = atoi(argv[3]);
    
    if(S_ISREG(finfo.st_mode)){
        
        int fd = open(argv[1],O_RDONLY);
        osAssert(-1!=fd,"Open failed");
        osAssert(((off_t) -1)!=lseek(fd,offset,SEEK_SET),"Seek failed");
        
        int buffsize = 1<<13;
        char *bufer=malloc(buffsize);
        osAssert(NULL!=bufer, "Malloc failed");
        
        int procitano=read(fd,bufer,duzina);
        osAssert(procitano!=-1,"Read failed");
        bufer[procitano]=0;
        osAssert(-1!=write(STDOUT_FILENO,bufer,procitano+1),"Write failed");
        close(fd);
        free(bufer);        
    }
    else
        osAssert(0,"Not regular");
    
    return 0;
}
