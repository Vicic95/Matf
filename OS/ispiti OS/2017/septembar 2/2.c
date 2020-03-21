#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

#define MAX_WORD_LEN (256)

#define CHECK(expr, msg) \
    do { \
        if (!(expr)) { \
            perror(msg); \
            exit(1); \
        } \
    } while (0)
    
int main(int argc, char **argv)
{
  CHECK(2 == argc, "Wrong cmd args num");
  char *fpath = argv[1];
  FILE *file = fopen(fpath, "r+");
  CHECK(NULL != file, "File open failed");
  int fileFd = fileno(file);
  CHECK(-1 != fileFd, "Fileno failed");
  
  char currentWord[MAX_WORD_LEN];
  struct flock lock;
  while (1 == fscanf(file, "%s", currentWord)) {
    int number;
    if (sscanf(currentWord, "%d", &number) == 1 && number > 999 && number < 10000) {
      lock.l_type = F_WRLCK;
      lock.l_whence = SEEK_SET;
      lock.l_start = ftell(file);
      lock.l_len = -4;
      if (-1 != fcntl(fileFd, F_SETLK, &lock)) {
        CHECK(-1 != fseek(file, -4, SEEK_CUR), "Fseek failed");
        fprintf(file, "####");
      } else if (errno != EAGAIN) {
        CHECK(0, "Fcntl failed");
      } 
    }
  }

  fclose(file);
  return 0;
}
