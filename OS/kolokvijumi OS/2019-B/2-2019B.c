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
    osAssert(argc == 3, "Pogresni argumenti");
    struct stat fInfo1;
    struct stat fInfo2;
    
    osAssert(lstat(argv[1],&fInfo1) != -1, "lstat prvi");
    osAssert(lstat(argv[2],&fInfo2) != -1, "lstat drugi");
    
    if((fInfo1.st_mtime - fInfo2.st_mtime)>0){
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
