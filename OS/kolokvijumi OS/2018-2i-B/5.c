#define _XOPEN_SOURCE 700

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>

#include <ftw.h>
#include <string.h>

#define osAssert(expr,msg){\
    if(!(expr)){\
        perror(msg);\
        exit(EXIT_FAILURE);\
    }\
}while(0)

static char* osExt=NULL;

int funkcija (const char *fpath, const struct stat *sb,int typeflag, struct FTW *ftwbuf){
    
    if(S_ISREG(sb->st_mode) && ftwbuf->level>=2 && ftwbuf->level<=5) {
        char *ext = strrchr(fpath,'.');
        if(ext!=NULL && !strcmp(ext,osExt)){
            printf("%s\n",fpath+ftwbuf->base);
        }
       
    }
     return 0;
}

int main(int argc, char **argv) {
    
    osAssert(3==argc,"Args");
    
    struct stat finfo;
    osAssert(-1!=lstat(argv[1],&finfo),"Stat failed");
    
    osAssert(S_ISDIR(finfo.st_mode),"Not dir");
    
    osExt=argv[2];
    
    osAssert(-1!=nftw(argv[1],funkcija,100,0),"NFTW failed");
    
    return 0;
}
