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


void osMkPublicDir(const char* dname) {
    
    mode_t mode =0777;
    mode_t oldUmask = umask(0);
    osAssert(-1!=mkdir(dname,mode),"Mkdir failed");
    umask(oldUmask);
}

int main(int argc, char **argv) {
    osAssert(2==argc,"Args");
    
    osMkPublicDir(argv[1]);
     
    return 0;
}
