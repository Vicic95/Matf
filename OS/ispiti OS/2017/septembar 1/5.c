#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <semaphore.h>

#define ARRAY_MAX (1024)

#define CHECK(expr, msg) \
    do { \
        if (!(expr)) { \
            perror(msg); \
            exit(1); \
        } \
    } while (0)
    
typedef struct {
    sem_t inDataReady;
    int array[ARRAY_MAX];
    unsigned arrayLen;
} OsData;

int osIsPowerOf3(int x)
{
    if (x == 1)
        return 1;
    else if (x % 3 == 0)
        return osIsPowerOf3(x/3);
    else 
        return 0;
}

int main(int argc, char **argv)
{
  // Check cmd args
  CHECK(2 == argc, "Args");
  char *shmName = argv[1];
  
  // Open shm
  int shmFd = shm_open(shmName, O_RDWR, 0);
  CHECK(-1 != shmFd, "Open shm failed");
  struct stat shmInfo;
  CHECK(-1 != fstat(shmFd, &shmInfo), "Getting shm info failed");
  OsData *pData = mmap(NULL, shmInfo.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, shmFd, 0);
  CHECK(MAP_FAILED != pData, "Mmap failed");
  
  // Wait on semaphore
  CHECK(-1 != sem_wait(&pData->inDataReady), "Waiting on semaphore failed");
  
  // Print numbers
  int *array = pData->array;
  for (int i = 0; i < pData->arrayLen; ++i)
      if (osIsPowerOf3(array[i]))
        printf("%d\n", array[i]);
  
  // Release fd and memory
  close(shmFd);
  munmap(pData, shmInfo.st_size);
  return 0;
}
