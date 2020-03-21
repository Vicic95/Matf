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
#include <grp.h>
#include <pwd.h>

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
    
    struct passwd *userInfo = getpwuid(finfo.st_uid);
    osAssert(NULL != userInfo, "Username failed");
    
    struct group *grInfo = getgrgid(finfo.st_gid);
    osAssert(NULL != grInfo, "Getgrgid failed");
    
    printf("%s %s\n",userInfo->pw_name,grInfo->gr_name);
 
    return 0;
}


