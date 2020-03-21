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
#include <poll.h>
#include <strings.h>
#include <string.h>

#define osAssert(expr,msg){\
    if(!(expr)){\
        perror(msg);\
        exit(EXIT_FAILURE);\
    }\
}while(0)

#define MAX_SIZE (256) 

int main(int argc, char** argv) {
	
	osAssert(argc >= 2, "Args");
	
	unsigned int numFifos = argc - 1;

	struct pollfd* fileMonitors = calloc(numFifos, sizeof(struct pollfd));
	osAssert(fileMonitors != NULL, "calloc failed");
	FILE** streams = malloc(numFifos*sizeof(FILE*));
	osAssert(streams != NULL, "malloc failed");
	
	int i;
	for (i = 0; i < numFifos; i++) {
		fileMonitors[i].fd = open(argv[i + 1], O_RDONLY | O_NONBLOCK);
		osAssert(fileMonitors[i].fd != -1, "open failed");
		fileMonitors[i].events = POLLIN | POLLHUP | POLLERR;
		streams[i] = fdopen(fileMonitors[i].fd, "r");
		osAssert(streams[i] != NULL, "fdopen failed");
	}
	
	int read_num;
	char* max_num;
	int max_read;
	int initialized = 0;
	int numActive = numFifos;
	while (numActive) {
		
		int events = poll(fileMonitors, numFifos, -1);
		osAssert(events != -1, "poll failed");
		
		
		for (i = 0; i < numFifos; i++) {
			
			if (fileMonitors[i].revents & POLLIN) {
				
				while (fscanf(streams[i],"%d", &read_num) == 1) {
						
					if (!initialized) {
						max_num = argv[i+1];
						max_read = read_num;
						initialized = 1;
					}
					else {
						
						if (read_num > max_read) {
							
							max_read = read_num;
							max_num = argv[i+1];
						}
					}
				}
				
				fileMonitors[i].revents = 0;
			}
			else if (fileMonitors[i].revents & (POLLHUP | POLLERR)) {
				
				fclose(streams[i]);
				fileMonitors[i].fd = -1;
				fileMonitors[i].revents = 0;
				fileMonitors[i].events = 0;
				numActive--;
			}
		}		
	}
	
	char* name = strrchr(max_num, '/');
	printf("%d %s\n", max_read, name != NULL ? (name+1) : max_num);	
	
	free(fileMonitors);
	free(streams);
	
	exit(EXIT_SUCCESS);
}
