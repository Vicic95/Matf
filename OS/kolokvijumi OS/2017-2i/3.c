#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include <errno.h>
#include  <time.h>

#define osAssert(expr,msg){\
    if(!(expr)){\
        perror(msg);\
        exit(EXIT_FAILURE);\
    }\
}while(0)

unsigned osNumOfDaysFileModified(const char* fpath){
    
    time_t vreme = time(NULL);
    osAssert(vreme != ((time_t) -1), "Time failed");
    
    struct stat finfo;
    osAssert(-1!=stat(fpath,&finfo),"Stat failed");
    
    
    return ((vreme-finfo.st_mtime)/(24*60*60));
}

int main(int argc, char **argv) {
    osAssert(2==argc, "Args");
    
    printf("%u\n",osNumOfDaysFileModified(argv[1]));
 
    return 0;
}
