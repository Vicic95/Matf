#define _XOPEN_SOURCE 700

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h> 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <math.h>

#define osAssert(expr,msg){\
    if(!(expr)){\
        perror(msg);\
        exit(EXIT_FAILURE);\
    }\
}while(0)

int main(int argc, char** argv){
    
    osAssert(3==argc,"Args");
    
    struct stat finfo;
    
    osAssert(-1!=lstat(argv[1],&finfo),"Stat failed");
    char *file = strrchr(argv[1],'/');
    
    if(!strcmp(argv[2],"KB")){
        
        if(file!=NULL){
        char *name = malloc(strlen(file));
        osAssert(NULL!=name,"Malloc failed");
        strcpy(name,file+1);
        printf("%s %dKB\n",name,(int)ceil(1.0*finfo.st_size/1024));
        free(name);
        }
        
        else
            printf("%s %dKB\n",argv[1],(int)ceil(1.0*finfo.st_size/1024));
    }
    else if(!strcmp(argv[2],"MB")){ if(file!=NULL){
        char *name = malloc(strlen(file));
        osAssert(NULL!=name,"Malloc failed");
        strcpy(name,file+1);
        printf("%s %dMB\n",name,(int)ceil(1.0*finfo.st_size/1024/1024));
        free(name);
    }
        else
            printf("%s %dMB\n",argv[1],(int)ceil(1.0*finfo.st_size/1024/1024));
    }
    else if(!strcmp(argv[2],"GB")){
      if(file!=NULL){
        char *name = malloc(strlen(file));
        osAssert(NULL!=name,"Malloc failed");
        strcpy(name,file+1);
        printf("%s %dGB\n",name,(int)ceil(1.0*finfo.st_size/1024/1024/1024));
        
          free(name);
      }
        else
            printf("%s %dGB\n",argv[1],(int)ceil(1.0*finfo.st_size/1024/1024/1024));
    }
    else
        osAssert(0,"wrong option");
    
    return 0;
}
