#define _XOPEN_SOURCE 700

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include <errno.h>
#include <limits.h>
#include <string.h>

#define osAssert(expr,msg){\
    if(!(expr)){\
        perror(msg);\
        exit(EXIT_FAILURE);\
    }\
}while(0)

unsigned funkcija(const char* fpath) {
    
    struct stat finfo;
    char *abPath = realpath(fpath,NULL);
    osAssert(NULL!=abPath,"Realpath failed");
    osAssert(-1!=stat(abPath,&finfo),"Stat failed");
    
    if(!(finfo.st_mode & S_IRWXO))
        return strlen(abPath);
    else 
        return 0;
    free(abPath);
}

int main(int argc, char **argv) {
    osAssert(2<=argc,"Args");
    
    for(unsigned i=1;i<argc;i++){
        
            struct stat finfo;
            char *abPath = realpath(argv[i],NULL);
            osAssert(NULL!=abPath,"Realpath failed");
            osAssert(-1!=stat(abPath,&finfo),"Stat failed");
            if(!(S_ISDIR(finfo.st_mode)))
                osAssert(0,"Isn't directory");
            
            free(abPath);
    }    
    for(unsigned i=0;i<argc;i++){
        unsigned rez = funkcija(argv[i]);
        if(rez)
            printf("%u\n",rez);
    }
     
    return 0;
}
