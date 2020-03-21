#define _XOPEN_SOURCE 700

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <string.h>
#include <errno.h>
#include <limits.h>
#include <dirent.h>

#define osAssert(expr,msg){\
    if(!(expr)){\
        perror(msg);\
        exit(EXIT_FAILURE);\
    }\
}while(0)

static long long int max = -1;
static long long int min = LLONG_MAX;

void osTreeWalk(char* fpath){
    
    struct stat finfo;
    osAssert(-1!=lstat(fpath,&finfo),"Stat failed");
    
    if(S_ISREG(finfo.st_mode)){
        if (finfo.st_size>max)
            max = finfo.st_size;
        if(finfo.st_size<min)
            min = finfo.st_size;
    }
    else if (S_ISDIR(finfo.st_mode)){
        
        DIR* dir = opendir(fpath);
        osAssert(NULL != dir, "Opendir failed");
        
        struct dirent* entry;
        while(NULL!=(entry=readdir(dir))){
            
            char* newPath = malloc(strlen(fpath)+1+strlen(entry->d_name)+1);
            osAssert(NULL!=newPath,"Malloc failed");
            
            strcpy(newPath,fpath);
            strcat(newPath,"/");
            strcat(newPath,entry->d_name);
            
            if(!strcmp(entry->d_name,".") || !strcmp(entry->d_name,".."))
                continue;
            
            osTreeWalk(newPath);
            free(newPath);
            
        }
        osAssert(0==errno,"Readdir failed");
        osAssert(-1!=closedir(dir),"Closedir failed");
        
    }
    else
        return;
    
}
int main(int argc, char** argv){
    
    osAssert(2==argc, "Args");
    
    struct stat finfo;
    osAssert(-1!=lstat(argv[1],&finfo),"Stat failed");
    
    osAssert(S_ISDIR(finfo.st_mode),"Not a dir");
    
    osTreeWalk(argv[1]);
    
    printf("%lld\n",max-min);
    
    return 0;
}
