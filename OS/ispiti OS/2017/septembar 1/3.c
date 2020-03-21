#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include <sys/epoll.h>
#include <limits.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <float.h>

#define CHECK(expr, msg) \
    do { \
        if (!(expr)) { \
            perror(msg); \
            exit(1); \
        } \
    } while (false)

typedef struct
{
    FILE *file;
    float sum;
} OsFIFO;
    
int main(int argc, char **argv)
{
    CHECK(argc > 1, "Args");
    
    // Create epoll instance
    int epollFd = epoll_create(!0);
    CHECK(-1 != epollFd, "Failed to create epoll instance");
    
    // Allocate struct
    int fdsNum = argc-1;
    OsFIFO *data = calloc(fdsNum, sizeof *data);
    CHECK(NULL != data, "Allocating data failed");
    
    struct epoll_event currentEvent;
    currentEvent.events = EPOLLIN;
    for (int i = 1; i < argc; ++i)
    {
        int fd = open(argv[i], O_RDONLY | O_NONBLOCK);
        CHECK(-1 != fd, "Opening FIFO failed");
        data[i-1].file = fdopen(fd, "r");
        
        CHECK(data[i-1].file != NULL, "Fdopen failed");
        currentEvent.data.ptr = &data[i-1];
        CHECK(-1 != epoll_ctl(epollFd, EPOLL_CTL_ADD, fd, &currentEvent), "Registering event failed");
    }
    
    int fdsOpen = fdsNum;
    while (fdsOpen)
    {
        CHECK(-1 != epoll_wait(epollFd, &currentEvent, 1, -1), "Waiting for ready event failed");
        OsFIFO *current = currentEvent.data.ptr;
        if (currentEvent.events & EPOLLIN)
        {
            float next;
            while (1 == fscanf(current->file, "%f", &next)) 
                current->sum += next;
        }
        else if (currentEvent.events & (EPOLLHUP | EPOLLERR))
        {
            --fdsOpen;
            fclose(current->file);
        }
    }
    
    float maxSum = -FLT_MAX;
    const char *maxPath = NULL;
    for (int i = 0; i < fdsNum; ++i)
    {
        if (data[i].sum > maxSum)
        {
            maxSum = data[i].sum;
            maxPath = argv[i+1];
        }
    }
    printf("%s\n", maxPath);
    
    free(data);
    close(epollFd);
    return 0;
}
