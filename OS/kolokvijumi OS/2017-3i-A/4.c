#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include <errno.h>
#include <string.h>

#define osAssert(expr,msg){\
    if(!(expr)){\
        perror(msg);\
        exit(EXIT_FAILURE);\
    }\
}while(0)

int main(int argc, char **argv) {
    osAssert(3==argc,"args");
   
    if(!strcmp(argv[1],"-r")){
        
         struct stat finfo;
         osAssert(-1 != lstat(argv[2],&finfo),"Stat failed");
    
        if(!(S_ISREG(finfo.st_mode)))
            osAssert(0,"Isn't regular");
        
        int fd = open(argv[2],O_RDONLY);
        osAssert(-1!=fd, "Open failed");
        int bufsize = 1024;
        char *bufer = malloc(bufsize);
        osAssert(NULL != bufer, "Malloc failed");
        int procitano = read(fd,bufer,bufsize);
        osAssert(-1!=procitano, "Read failed");
        bufer[procitano]=0;
        osAssert(-1!=write(STDOUT_FILENO,bufer,strlen(bufer)),"write failed");
        free(bufer);
        close(fd);
        
    }
    else if (!strcmp(argv[1],"-w")){
        int fd = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0664);
        osAssert(-1 != fd, "Open failed");
        int bufsize = 1024;
        char *bufer = malloc(bufsize);
        osAssert(NULL != bufer, "Malloc failed");
        int procitano = read(STDIN_FILENO,bufer,bufsize);
        osAssert(-1 != procitano , "Read failed");
        bufer[procitano]=0;
        osAssert(-1!=write(fd,bufer,strlen(bufer)),"write failed");
        free(bufer);
        close(fd);
    }
    else if(!strcmp(argv[1],"-a")){
        
        int fd = open(argv[2], O_WRONLY | O_APPEND);
        osAssert(-1 != fd, "Open failed");
        int bufsize = 1024;
        char *bufer = malloc(bufsize);
        osAssert(NULL != bufer, "Malloc failed");
        int procitano = read(STDIN_FILENO,bufer,bufsize);
        osAssert(-1 != procitano , "Read failed");
        bufer[procitano]=0;
        osAssert(-1!=write(fd,bufer,strlen(bufer)),"write failed");
        free(bufer);
        close(fd);
        
    }
    else
        osAssert(0,"Wrong argument");
    return 0;
}
