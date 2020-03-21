#define _XOPEN_SOURCE 700

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h> 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <dirent.h>
#include <errno.h>

#define osAssert(expr,msg){\
    if(!(expr)){\
        perror(msg);\
        exit(EXIT_FAILURE);\
    }\
}while(0)

static char* os_Ext=NULL;
static int br=0;

void osNtfw(const char* path) {
    
    struct stat finfo;
    
    osAssert(-1!=lstat(path,&finfo),"Stat failed");
    
    if(S_ISREG(finfo.st_mode)){
        char *ext = strrchr(path,'.');
        if(!strcmp(ext,os_Ext) && ext!=NULL)
            br++;
        
    }
    else if(S_ISDIR(finfo.st_mode)){
        
        DIR* dir=opendir(path);
        osAssert(NULL!=dir,"Opendir failed");
        
        errno=0;
        struct dirent* entry;
        while(NULL!=(entry=readdir(dir))){
            
            char* newPath=malloc(strlen(path)+1+strlen(entry->d_name)+1);
            osAssert(NULL!=newPath,"Malloc failed");
            strcpy(newPath,path);
            strcat(newPath,"/");
            strcat(newPath,entry->d_name);
                        
            if(!strcmp(entry->d_name,".") || !strcmp(entry->d_name,".."))
                continue;
            
            osNtfw(newPath);
            free(newPath);
        }
        osAssert(0==errno,"Readdir failed");
        
        osAssert(-1!=closedir(dir),"Closedir failed");
    }
    else
        return;
}
int main(int argc, char** argv){
    
    osAssert(3==argc,"Args");
    
    struct stat finfo;
    osAssert(-1!=lstat(argv[1],&finfo),"Stat failed");
    
    if(S_ISDIR(finfo.st_mode)){
        os_Ext=argv[2];
        osNtfw(argv[1]);
        printf("%d\n",br);
        
    }
    else
        osAssert(0,"Not dir");
        
    return 0;
}
