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

#include <poll.h>
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
	struct pollfd* fileMonitors = calloc(numFifos,sizeof(struct pollfd));
	osAssert(fileMonitors != NULL, "malloc failed");
	int* cnt = calloc(numFifos, sizeof(int));
	osAssert(cnt != NULL, "malloc failed");
	
	int i = 0;
	for (i = 0; i < numFifos; i++) {
		fileMonitors[i].fd = open(argv[i+1], O_RDONLY | O_NONBLOCK);
		osAssert(fileMonitors[i].fd != -1, "open failed");
		cnt[i] = 0;
		fileMonitors[i].events = POLLIN | POLLHUP | POLLERR;
	}
	
	int numActive = numFifos;
	
	int curr_max;
	char* curr_max_name;
	int initialized = 0;
	char buf[100];
	
	while (numActive) {
		
		int events = poll(fileMonitors, numFifos, -1);
		osAssert(events != -1, "poll failed");
		
		for (i = 0; i < numFifos; i++) {
			
			if (fileMonitors[i].revents & POLLIN) {
				
				int readBytes = 0;
					
				while ((readBytes = read(fileMonitors[i].fd, buf, 100)) > 0) {
					cnt[i] += readBytes;
				}
				if (readBytes == -1) {
					if (errno != EAGAIN)
						osAssert(false,"read failed");
				}
				
				if (!initialized) {
						curr_max = cnt[i];
						curr_max_name = argv[i+1];
						initialized = 1;
				}
				else {
					if (cnt[i] > curr_max) {
						curr_max = cnt[i];
						curr_max_name = argv[i+1];
					}
				}
				
				fileMonitors[i].revents = 0;
			}
			else if (fileMonitors[i].revents & (POLLHUP | POLLERR)){
				
				close(fileMonitors[i].fd);
				fileMonitors[i].fd = -1;
				fileMonitors[i].events = 0;
				fileMonitors[i].revents = 0;
				numActive--;
			}
		}
	}
	
	char* name = strrchr(curr_max_name, '/');
	printf("%s\n", name != NULL ? name : curr_max_name);
	
	free(fileMonitors);
	free(cnt);
	 
	exit(EXIT_SUCCESS);
}
