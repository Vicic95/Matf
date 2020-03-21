#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdbool.h>
#include <string.h>

#define MAX_STOP_IDXS (2048)

#define CHECK(expr, msg) \
	do { \
		if (!(expr)) \
		{ \
			perror(msg); \
			exit(EXIT_FAILURE); \
		} \
	} while (false)

#define THREAD_CHECK(expr, msg) \
	do { \
		int __myErrno = expr; \
		if (__myErrno != 0) \
		{ \
			perror(msg); \
			exit(EXIT_FAILURE); \
		} \
	} while (false)

static const char *os_FilePath = NULL;
static int os_Tnum = -1;
static int os_StopIdxs[MAX_STOP_IDXS];
static int os_StopIdxsCnt = 0;
static pthread_mutex_t os_Lock = PTHREAD_MUTEX_INITIALIZER;

void osCntStr(int fd, int idx, const char *needle)
{
	int fsize = lseek(fd, 0, SEEK_END);
	CHECK(-1 != fsize, "Failed to get file size");

	int chunkSize = fsize / os_Tnum;
	int start = chunkSize * idx;
	CHECK(-1 != lseek(fd, start, SEEK_SET), "Failed to position in file");

	char *haystack = malloc(chunkSize+1);
	CHECK(NULL != haystack, "Failed to allocate buffer for processing");
	CHECK(chunkSize == read(fd, haystack, chunkSize), "Read into haystack failed");
	haystack[chunkSize] = 0;

	fprintf(stderr, "Searching for %s from %d in %d bytes in thread %d.\n", needle, start, chunkSize, idx);
	char *searchPos = haystack, *pos = NULL;
	while ((pos = strstr(searchPos, needle)))
	{
		THREAD_CHECK(pthread_mutex_lock(&os_Lock), "Locking mutex failed");
        os_StopIdxs[os_StopIdxsCnt++] = pos - haystack + start;
		THREAD_CHECK(pthread_mutex_unlock(&os_Lock), "Unlocking mutex failed");

        searchPos = pos + 1;
	}

	free(haystack);
}

void* osThreadMain(void *arg)
{
	int idx = (int)(intptr_t)arg;
	int fd = open(os_FilePath, O_RDONLY);
	CHECK(-1 != fd, "Failed to open the file");
	osCntStr(fd, idx, "tag");
	osCntStr(fd, idx, "taa");
	osCntStr(fd, idx, "tga");
	close(fd);
	return NULL;
}

int main(int argc, char const *argv[])
{
	CHECK(3 == argc, "Wrong cmd args num");

	os_Tnum = atoi(argv[1]);
	os_FilePath = argv[2];

	pthread_t *tids = malloc(os_Tnum * sizeof *tids);
	CHECK(NULL != tids, "Failed to allocate threads");
	for (int i = 0; i < os_Tnum; ++i)
	{
		THREAD_CHECK(pthread_create(tids+i, NULL, osThreadMain, (void*)(intptr_t)i), "Failed to create a thread");
	}
		
	for (int i = 0; i < os_Tnum; ++i)
	{
		THREAD_CHECK(pthread_join(tids[i], NULL), "Failed to join a thread");
	}

	while(os_StopIdxsCnt--)
		printf("%d ", os_StopIdxs[os_StopIdxsCnt]);
	printf("\n");

	free(tids);
	THREAD_CHECK(pthread_mutex_destroy(&os_Lock), "Destroying mutex failed");
	return 0;
}
