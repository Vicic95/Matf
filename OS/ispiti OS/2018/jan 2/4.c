#define _XOPEN_SOURCE 700
#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <string.h>

#include <sys/epoll.h>
#include <signal.h>
#include <errno.h>


#define osAssert(expr,msg){\
    if(!(expr)){\
        perror(msg);\
        exit(EXIT_FAILURE);\
    }\
}while(0)

int main(int argc, char** argv) {
	
	osAssert(argc > 2, "Args");
	
	int numFifos = argc - 1;
	int epollFd = epoll_create(numFifos);
	osAssert(epollFd != -1, "epoll_create failed");
	
	int* fds = malloc(numFifos*sizeof(int));
	int* fds_read = malloc(numFifos*sizeof(int));
	osAssert(fds != NULL, "malloc failed");
	osAssert(fds_read != NULL, "malloc failed");
	
	struct epoll_event currentEvent;
	int i;
	for (i = 0; i < numFifos; i++) {
		
		memset(&currentEvent, 0, sizeof(struct epoll_event));
		currentEvent.events |= EPOLLIN | EPOLLHUP | EPOLLERR;
		
		currentEvent.data.fd = open(argv[i+1], O_RDONLY | O_NONBLOCK);
		osAssert(currentEvent.data.fd != -1, "open failed");
		fds[i] = currentEvent.data.fd;
		
		osAssert(epoll_ctl(epollFd, EPOLL_CTL_ADD, currentEvent.data.fd, &currentEvent) != -1, "epoll add failed");
	} 
	
	struct epoll_event readyList[10];
	int min_read;
	int min_fd;
	int numActive = numFifos;
	while (numActive) {
		
		int numOfReadyEvents = epoll_wait(epollFd, readyList, 10, -1);
		osAssert(numOfReadyEvents != -1, "epoll wait failed");
		
		char buf[100];
		int k;
		for (k = 0; k < numOfReadyEvents; k++) {
			
			if (readyList[k].events & EPOLLIN) {
				
				int bytesRead = 0;
				int total = 0;
				int fd_active = readyList[k].data.fd;
				
				while ((bytesRead = read(readyList[k].data.fd, buf, 100)) > 0) {
					total += bytesRead;
				}
				
				if (bytesRead == -1)
					if (errno != EAGAIN)
						osAssert(false, "read failed");
					
				int j = 0;
				for (j = 0; j < numFifos; j++) {
					if (fds[j] == readyList[k].data.fd) {
						fds_read[j] += total;
					}						
				}
			}
			else if (readyList[k].events & (EPOLLHUP | EPOLLERR)) {
				
				close(readyList[k].data.fd);
				numActive--;
			}
		}
	}
	
	min_read = fds_read[0];
	min_fd = 0;
	
	for (i = 0; i < numFifos; i++) {
		if (fds_read[i] < min_read) {
			min_fd = i;
			min_read = fds_read[i];
		}
	}
	
	char* name = strrchr(argv[min_fd+1], '/');
	printf("%s\n", name != NULL ? name : argv[min_fd + 1]);
	 
	free(fds);
	close(epollFd);
	 
	exit(EXIT_SUCCESS);
}
