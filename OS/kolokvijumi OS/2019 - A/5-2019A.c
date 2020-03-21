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

#define MAX_SIZE (1024)
int main(int argc,char** argv){
    osAssert(argc == 2 , "argumenti");
    struct stat fInfo;
    osAssert(lstat(argv[1],&fInfo)!=-1,"lstat");
    if(S_ISLNK(fInfo.st_mode)){
        char* buf = malloc(MAX_SIZE);
        osAssert(buf!=NULL,"buf");
        readlink(argv[1],buf,MAX_SIZE);
        printf("%s",buf);
        free(buf);
    }
    else
        osAssert(0,"nije link");

    exit(EXIT_SUCCESS);
}
