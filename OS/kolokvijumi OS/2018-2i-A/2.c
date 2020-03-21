
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include <errno.h>
#include <string.h>

#define osAssert(expr,msg){\
    if(!(expr)){\
        perror(msg);\
        exit(EXIT_FAILURE);\
    }\
}while(0)

int main(int argc, char **argv) {
    osAssert(3==argc, "Args");
    
    struct stat finfo;
    osAssert(-1 != stat(argv[1],&finfo), "Stat failed");
    osAssert(S_ISDIR(finfo.st_mode), "Isn't directory");
    
    char *s = strrchr(argv[1],'/');
    if(s==NULL){
        osAssert(-1 != rename(argv[1],argv[2]), "Rename failed");
    }else {
        
        char *path = malloc(strlen(argv[1]) - strlen(s) + strlen(argv[2]) +2);
        strncpy(path,argv[1],strlen(argv[1])-strlen(s)+1);
        strcat(path,argv[2]);
        osAssert(-1 != rename(argv[1],path), "Rename failed");
        
    }
    return 0;
}


