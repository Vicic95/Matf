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
    osAssert(argc == 3, "argumenti");
    
    struct stat fInfo1;
    struct stat fInfo2;
    
    osAssert(lstat(argv[1],&fInfo1)!= -1, "prvi");
    osAssert(lstat(argv[2],&fInfo2)!= -1, "drugi");
    
    int mask1 = 0700;
    int mask2 = 0070;
    int mask3 = 0007;
    
    int ow = fInfo1.st_mode & mask1;
    int gr = fInfo1.st_mode & mask2;
    int ot = fInfo1.st_mode & mask3;
    int mode = 0;
    mode |= (gr << 3);
    mode |= (ot << 3);
    mode |= (ow >> 6);
    
    osAssert(chmod(argv[2],mode)!=-1,"chmod");

    exit(EXIT_SUCCESS);
}
