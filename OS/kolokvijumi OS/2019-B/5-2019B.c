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
#include <dirent.h>

#define osAssert(expr,msg){\
    if(!(expr)){\
        perror(msg);\
        exit(EXIT_FAILURE);\
    }\
}while(0)

void osWalk(const char* fpath){
    
    struct stat finfo;
    
    osAssert(-1!=lstat(fpath,&finfo),"Stat failed");
    
    char* rPath = realpath(fpath,NULL);
    char* ima = strstr(rPath,"/dir_");
    
    if(ima!=NULL && S_ISREG(finfo.st_mode)){
        char *name = strrchr(rPath,'/');
        if(name!=NULL)
            printf("%s\n",name+1);
        
    }else if(S_ISDIR(finfo.st_mode)){
        
        DIR* dir = opendir(fpath);
        osAssert(NULL!=dir,"Open  failed");
        
        struct dirent* entry;
        errno=0;
        while(NULL!=(entry=readdir(dir))){
            
            if(!strcmp(entry->d_name,".") || !strcmp(entry->d_name,".."))
                continue;
            
            char* newPath = malloc(strlen(fpath)+1+strlen(entry->d_name)+1);
            osAssert(NULL!=newPath,"Malloc failed");
            strcpy(newPath,fpath);
            strcat(newPath,"/");
            strcat(newPath,entry->d_name);
            osWalk(newPath);
            free(newPath);
            
        }
        
        osAssert(errno==0,"Readdir failed");
        
        osAssert(-1!=closedir(dir),"Closedir failed");
    }
    
    

    free(rPath);
}


int main(int argc, char **argv) {
    osAssert(2==argc,"Wrong num of args");
    
    struct stat finfo;
    
    osAssert(-1!=lstat(argv[1],&finfo),"Stat failed");
    
    if(!S_ISDIR(finfo.st_mode)){
        osAssert(0,"Not dir");
    }else
        osWalk(argv[1]);
 
    return 0;
}


