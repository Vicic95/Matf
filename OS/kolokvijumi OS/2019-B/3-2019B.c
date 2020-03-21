#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define osAssert(expr,msg){\
    if(!(expr)){\
        perror(msg);\
        exit(EXIT_FAILURE);\
    }\
}while(0)

int main(int argc,char** argv){
    osAssert(argc == 4, "Pogresni arguenti");
    
    struct stat fInfo;
    osAssert(lstat(argv[1],&fInfo) != -1, "lstat");
    
    if(!S_ISREG(fInfo.st_mode))
        osAssert(0,"nije regularan");
    
    int p = atoi(argv[2]);
    int n = atoi(argv[3]);
    
    int fd = open(argv[1],O_RDWR);
    osAssert(fd!= -1, "open");
    osAssert(lseek(fd,p,SEEK_SET)!=-1,"lseek");
    char* buffer = malloc(n);
    osAssert(buffer!= NULL, "buffer n");
    osAssert(0<=read(fd,buffer,n),"read");
    char* novi = malloc(n);
    osAssert(novi != NULL, "novi ");
    int i;
    for(i=0;i<strlen(buffer);i++)
        novi[i] = buffer[strlen(buffer)- i-1];
    osAssert(lseek(fd,p,SEEK_SET) != -1, "lseek2");
    osAssert(write(fd,novi,n)!=-1,"write");
    
    
    
    close(fd);
    free(buffer);
    free(novi);

    exit(EXIT_SUCCESS);
}
