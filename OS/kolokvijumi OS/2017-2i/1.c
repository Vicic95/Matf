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

bool isPublicFile(const char* fpath) {
    
    struct stat finfo;
    osAssert(-1!=stat(fpath,&finfo),"Stat failed");
    
    if (!(S_ISREG(finfo.st_mode)))
        osAssert(0,"File isn't regular");

    return ((finfo.st_mode & S_IROTH) && (finfo.st_mode & S_IWOTH));
}

int main(int argc, char **argv) {
    osAssert(2==argc,"Args");
    
    if (isPublicFile(argv[1]))
        printf("true\n");
    else
        printf("false\n");
     
    return 0;
}
