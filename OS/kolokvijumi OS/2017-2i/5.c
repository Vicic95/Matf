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
#include <string.h>
#include <time.h>

#define osAssert(expr,msg){\
    if(!(expr)){\
        perror(msg);\
        exit(EXIT_FAILURE);\
    }\
}while(0)

static char* ulaz=NULL;

unsigned osNumOfDaysFileModified(const char* fpath){
        
    time_t vreme = time(NULL);
    osAssert(vreme != ((time_t) -1), "Time failed");
    
    struct stat finfo;
    osAssert(-1!=stat(fpath,&finfo),"Stat failed");
    
    
    return ((vreme-finfo.st_mtime)/(24*60*60));
}

int funkcija (const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf){
        
    if (typeflag == FTW_F){
        unsigned dani = osNumOfDaysFileModified(fpath);
        if(dani<30){
    
            char *destPath = malloc(strlen(ulaz)+1+strlen(fpath+ftwbuf->base)+1);
            osAssert(NULL!=destPath,"Malloc failed");
            strcpy(destPath,ulaz);
            strcat(destPath,"/");
            strcat(destPath,fpath+ftwbuf->base);
            osAssert(-1!=rename(fpath,destPath),"Rename failed");
            free(destPath);
        }
        else
            osAssert(-1!=unlink(fpath),"Unlink failed");
        
    }         
    
    
    return 0;
}

bool isPublicFile(const char* fpath) {
    
    struct stat finfo;
    osAssert(-1!=stat(fpath,&finfo),"Stat failed");
    
    if (!(S_ISREG(finfo.st_mode)))
        osAssert(0,"File isn't regular");
    
    
    return ((finfo.st_mode & S_IROTH) && (finfo.st_mode & S_IWOTH));
       
}

void osMkPublicDir(const char* dname) {
    
    mode_t mode =0777;
    
    mode_t oldUmask = umask(0);
    
    osAssert(-1!=mkdir(dname,mode),"Mkdir failed");
    
    umask(oldUmask);
}





int main(int argc, char **argv) {
    osAssert(3==argc, "Args");
    
    struct stat finfo;
    osAssert(-1!=lstat(argv[1],&finfo),"Stat failed");
    
    ulaz = argv[2];
    
    if(S_ISDIR(finfo.st_mode)){
        osMkPublicDir(argv[2]);
        osAssert(-1!=nftw(argv[1],funkcija,50,0),"NFTW failed");        
    }
    else
        osAssert(0,"Isn't dir");
 
    return 0;
}
