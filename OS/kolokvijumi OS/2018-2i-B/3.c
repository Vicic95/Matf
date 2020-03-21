
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
    osAssert(3==argc,"Args");
    
    struct stat finfo;
    osAssert(-1!=stat(argv[1],&finfo),"Stat failed");
    
    mode_t mode = finfo.st_mode;
    if(!strcmp(argv[2],"u+r")) mode |= 0400; 
    else 
         
    if(!strcmp(argv[2],"u+w")) mode |= 0200; 
    else 
         
    if(!strcmp(argv[2],"u+x")) mode |= 0100; 
    else 
         
    if(!strcmp(argv[2],"u-r")) mode &= 0377; 
    else 
         
    if(!strcmp(argv[2],"u-w")) mode &= 0577; 
    else 
         
    if(!strcmp(argv[2],"u-x")) mode &= 0677; 
    else 
         
    if(!strcmp(argv[2],"g+r")) mode |=0040; 
    else 
        
    if(!strcmp(argv[2],"g+w")) mode |=0020; 
    else 
         
    if(!strcmp(argv[2],"g+x")) mode |=0010; 
    else 
         
    if(!strcmp(argv[2],"g-r")) mode &= 0737; 
    else 
         
    if(!strcmp(argv[2],"g-w")) mode &= 0757; 
    else 
         
    if(!strcmp(argv[2],"g-x")) mode &= 0767; 
    else 
         
    if(!strcmp(argv[2],"o+r")) mode |=0004; 
    else 
         
    if(!strcmp(argv[2],"o+w")) mode |=0002; 
    else 
         
    if(!strcmp(argv[2],"o+x")) mode |=0001; 
    else 
         
    if(!strcmp(argv[2],"o-r")) mode &= 0773; 
    else 
         
    if(!strcmp(argv[2],"o-w")) mode &= 0775; 
    else 
         
    if(!strcmp(argv[2],"o-x")) mode &= 0776; 
    else
            
    osAssert(0,"Wrong mode given");
    
    osAssert(-1!=chmod(argv[1],mode),"Chmod failed");
    
    return 0;
}


