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
    osAssert(4==argc,"Args");
    
    long mode = strtol(argv[3],NULL,8);
    mode_t oldUmask = umask(0);
    
    if(!strcmp("-d",argv[1])){
        int fd = mkdir(argv[2], mode);
        if (errno == EEXIST) {
            int ch=chmod(argv[2],mode);
            osAssert(ch!=-1,"Chmod failed");
        }
        else 
            osAssert(fd!=-1, "Mkdir failed");
        close(fd);
    }
    else if (!strcmp("-f",argv[1])) {
        
        int fd = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT | O_EXCL, mode);
        if (fd==-1 && errno==EEXIST) {
            int ch=chmod(argv[2],mode);
            osAssert(ch!=-1,"Chmod failed");
        }
        else
            osAssert(fd!=-1,"Open failed");
        close(fd);
    
    }
    else
        osAssert(0, "Use -d or -f");
    
     umask(oldUmask);
 
    return 0;
}
