#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <pthread.h>
#include <errno.h>

#define CHECK(cond, msg) \
    do{ \
        if (!(cond)) { \
            perror((msg)); \
            exit(EXIT_FAILURE); \
        } \
    } while (false)
    
#define PTHREAD_CHECK(pthread_call, msg) \
    do{ \
      int __pthreadErrno = pthread_call; \
      if (__pthreadErrno) { \
        errno = __pthreadErrno; \
        perror(msg); \
        exit(EXIT_FAILURE); \
      } \
    } while (false)
    
pthread_mutex_t os_Lock = PTHREAD_MUTEX_INITIALIZER;
unsigned os_N = 0;
int *os_Matrix = NULL;
int os_Vertex = 0;
unsigned os_MaxInDegree = 0;

void* osThreadMain(void *arg) {
  unsigned vertexIdx = (unsigned)(intptr_t)arg;
  unsigned inDegree = 0;
  for (unsigned i = 0; i < os_N; ++i)
    inDegree += os_Matrix[i * os_N + vertexIdx];
  
  PTHREAD_CHECK(pthread_mutex_lock(&os_Lock), "Failed to lock mutex");
  if (inDegree > os_MaxInDegree) {
    os_MaxInDegree = inDegree;
    os_Vertex = vertexIdx;
  }
  PTHREAD_CHECK(pthread_mutex_unlock(&os_Lock), "Failed to unlock mutex");
  return NULL;
}

int main() {
    scanf("%u", &os_N);
    os_Matrix = malloc(os_N * os_N * sizeof *os_Matrix);
    CHECK(os_Matrix, "Failed to allocate graph matrix");
    
    for (unsigned i = 0; i < os_N * os_N; ++i)
      scanf("%d", &os_Matrix[i]);
    
    pthread_t *tids = malloc(os_N * sizeof *tids);
    for (unsigned i = 0; i < os_N; ++i)
      PTHREAD_CHECK(pthread_create(tids + i, NULL, osThreadMain, (void*)(intptr_t)i), "Failed to create thread");
    for (unsigned i = 0; i < os_N; ++i)
      PTHREAD_CHECK(pthread_join(tids[i], NULL), "Failed to join thread");
    
    free(tids);
    free(os_Matrix);
    PTHREAD_CHECK(pthread_mutex_destroy(&os_Lock), "Failed to destroy the mutex");
    
    printf("%d\n", os_Vertex);
    return 0;
}
