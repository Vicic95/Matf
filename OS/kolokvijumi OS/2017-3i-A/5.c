#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include <ftw.h>
#include <errno.h>

#define osAssert(expr,msg){\
    if(!(expr)){\
        perror(msg);\
        exit(EXIT_FAILURE);\
    }\
}while(0)

static int reg=0;
static int dir=0;
static int car=0;
static int blc=0;
static int lnk=0;
static int fifo=0;
static int soc=0;
static int ukupno =0;

 int funkcija (const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf){     
     switch (sb->st_mode & S_IFMT) {
           case S_IFBLK:  blc++;    ukupno++;                break;
           case S_IFCHR:  car++;    ukupno++;                break;
           case S_IFDIR:  dir++;    ukupno++;                break;
           case S_IFIFO:  fifo++;   ukupno++;                break;
           case S_IFLNK:  lnk++;    ukupno++;                break;
           case S_IFREG:  reg++;    ukupno++;                break;
           case S_IFSOCK: soc++;    ukupno++;                break;
           default: osAssert(0,"Mistake");                   break;
     }
     return 0;
}

int main(int argc, char **argv) {
    osAssert(2==argc,"Args");
    
    struct stat finfo;
    
    osAssert(-1!=lstat(argv[1],&finfo),"Lstat failed");
    
    osAssert(S_ISDIR(finfo.st_mode),"Not a dir");
    
    osAssert(-1!=nftw(argv[1],funkcija,50,FTW_PHYS),"NTFW failed");
    
    printf("%d %d %d %d %d %d %d %d\n",reg,dir,car,blc,lnk,fifo,soc,ukupno);
    
    return 0;
}
