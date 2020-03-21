
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include <errno.h>
#include <utime.h>

#define osAssert(expr,msg){\
    if(!(expr)){\
        perror(msg);\
        exit(EXIT_FAILURE);\
    }\
}while(0)

void osSek(const char* path, long int sek){
    
    struct utimbuf time;
    
    time.actime = sek;
    time.modtime = sek;
    osAssert(-1 != utime(path,&time), "Utime failed");
    
}
int main(int argc, char **argv) {
    osAssert(3==argc,"Args");
    long int sekunde = strtol(argv[2],NULL,10);
    osSek(argv[1],sekunde);
    
 
    return 0;
    }
    
    


