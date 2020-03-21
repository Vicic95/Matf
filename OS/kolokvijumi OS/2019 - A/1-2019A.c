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
    osAssert(argc == 3, "argumenti");
    struct stat fInfo;
    osAssert(lstat(argv[1],&fInfo)!= -1 ,"lstat");
    struct stat fInfo1;
    osAssert(lstat(argv[2],&fInfo1)!= -1 ,"lstat");
    
    
    if(fInfo.st_size > fInfo1.st_size){
        char* name = strrchr(argv[1], '/');
        if(NULL != name)
            printf("%s" , name);
        else
            printf("%s", argv[1]);
    }
    else{
        char* name = strrchr(argv[2], '/');
        if(NULL != name)
            printf("%s" , name);
        else
            printf("%s", argv[2]);
        
    }
    exit(EXIT_SUCCESS);
}
