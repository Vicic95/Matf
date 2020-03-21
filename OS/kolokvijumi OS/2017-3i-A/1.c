#define  _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <errno.h>

#define osAssert(expr,msg){\
    if(!(expr)){\
        perror(msg);\
        exit(EXIT_FAILURE);\
    }\
}while(0)


int main(int argc, char **argv) {
    osAssert(2==argc, "Args");
    
    struct stat finfo;
    
    osAssert(-1!=lstat(argv[1],&finfo),"Stat failed");
    
    if(S_ISDIR(finfo.st_mode) || S_ISREG(finfo.st_mode)){
        
        char str[10] = "-rwxrwxrwx";
        if(S_ISDIR(finfo.st_mode))
            str[0]='d';
        
        if(!(finfo.st_mode & S_IRUSR)) str[1]='-';
        if(!(finfo.st_mode & S_IWUSR)) str[2]='-';
        if(!(finfo.st_mode & S_IXUSR)) str[3]='-';
        
        if(!(finfo.st_mode & S_IRGRP)) str[4]='-';
        if(!(finfo.st_mode & S_IWGRP)) str[5]='-';
        if(!(finfo.st_mode & S_IXGRP)) str[6]='-';
        
        if(!(finfo.st_mode & S_IROTH)) str[7]='-';
        if(!(finfo.st_mode & S_IWOTH)) str[8]='-';
        if(!(finfo.st_mode & S_IXOTH)) str[9]='-';
        
        printf("%s\n",str);
    }
    else
        osAssert(0,"Not reg or dir");
     
    return 0;
}
