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
    
    FILE* in = fopen(argv[1],"r");
    osAssert(in!=NULL,"Opening failed");
    
    int fd2 = open(argv[2],O_RDWR | O_CREAT,0664);
    osAssert(-1!=fd2,"Open failed");
    
    int num;
    char str[1024];
    
    while(fscanf(in,"%d %s",&num,str)!=EOF){
        
        char *str1=malloc(strlen(str));
        osAssert(str1!=NULL, "Malloc failed");
        strcpy(str1,str);
                
        
        
        off_t lsize = lseek(fd2,num,SEEK_SET);
        osAssert(lsize!=(off_t)-1, "Lseek failed");
        

        osAssert(write(fd2,str1,strlen(str1))>0,"Write failed");
        free(str1);
    }
    
    fclose(in);
    close(fd2);
 
    return 0;
}
