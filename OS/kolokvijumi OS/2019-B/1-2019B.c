#include <syssssst.h>
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
    osAssert(argc == 2,"pogresni argumenti");
    
    struct stat fInfol;
    struct stat fInfos;
    
    osAssert(lstat(argv[1],&fInfol)!= -1,"lstat");
    osAssert(stat(argv[1],&fInfos)!= -1, "stat");
    
    if(!S_ISLNK(fInfol.st_mode))
        osAssert(0,"not link");
    
    if(fInfol.st_uid == fInfos.st_uid && fInfol.st_gid == fInfos.st_gid){
        printf("da\n");
        }
    else
        printf("ne\n");
    

    exit(EXIT_SUCCESS);
}
