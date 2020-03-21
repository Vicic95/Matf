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
    osAssert(4==argc,"Args");
    
    int fd = open(argv[1],O_RDONLY);
    osAssert(fd!=-1, "Open failed");
    
    long int a = strtol(argv[2],NULL,10);
    long int b = strtol(argv[3],NULL,10);
    
    osAssert(lseek(fd,a,SEEK_SET)!=(off_t)-1, "Lseek failed");
    char *str=malloc(b + 1);
    osAssert(str!=NULL, "Malloc failed");
    osAssert(read(fd,str,b)>=0,"Read failed");
    str[b] = '\0';
    printf("%s\n",str);
    
    free(str);
    close(fd);
    
    return 0;
}


