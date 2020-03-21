#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


#define osAssert(expr,msg){\
    if(!(expr)){\
        perror(msg);\
        exit(EXIT_FAILURE);\
    }\
}while(0)

int main(int argc,char** argv){
    osAssert(argc == 5, "argumenti");
    struct stat fInfo;
    osAssert(lstat(argv[1],&fInfo)!=-1,"lsta");
    
    if(!S_ISREG(fInfo.st_mode))
        osAssert(0,"nije reg");
    int p1 = atoi(argv[2]);
    int p2 = atoi(argv[3]);
    int n = atoi(argv[4]);
    

    int fd = open(argv[1],O_RDWR);
    osAssert(fd!=-1,"fd open");
    osAssert(lseek(fd,p1,SEEK_SET)!=-1,"lseek");
    char* buf1 = malloc(n);
    osAssert(buf1!=NULL, "buf1");
    osAssert(read(fd,buf1,n)>=0,"read a");
    
    osAssert(lseek(fd,p2,SEEK_SET)!=-1,"lseek2");
    char* buf2 = malloc(n);
    osAssert(buf2!=NULL, "buf1");
    osAssert(read(fd,buf2,n)>=0,"read b");
   
    osAssert(lseek(fd,p1,SEEK_SET)!=-1,"lseek");
    osAssert(write(fd,buf2,n)!=-1,"write");
    osAssert(lseek(fd,p2,SEEK_SET)!=-1,"lseek");
    osAssert(write(fd,buf1,n)!=-1,"write");
    
    close(fd);
    free(buf1);
    free(buf2);
    
    exit(EXIT_SUCCESS);
}
