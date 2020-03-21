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
    osAssert(argc == 2,"argumenti");
    struct stat fInfo;
    osAssert(lstat(argv[1],&fInfo)!=-1,"lstat");
    
    int mask1 =0700;
    int mask2 =0070;
    int mask3 = 0007;
    
    int mode = 0;
    int ow = fInfo.st_mode & mask1;
    int gr = fInfo.st_mode & mask2;
    int ot = fInfo.st_mode & mask3;
    
    mode |= (gr << 3);
    mode |= (ot << 3);
    mode |= (ow >>6);
    osAssert(chmod(argv[1],mode)!=-1,"chmod");

    exit(EXIT_SUCCESS);
}
