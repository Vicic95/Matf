#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <poll.h>

#include <errno.h>

#define check_error(expr, userMsg) \
	do { \
		if (!(expr)) {\
			perror(userMsg); \
			exit(EXIT_FAILURE); \
		}\
	} while(0)

#define BUF_SIZE (256)

int main(int argc, char** argv) {
	
	check_error(argc > 1, "Args");
	
	struct pollfd* fds = malloc((argc-1)*sizeof(struct pollfd));
	check_error(fds != NULL, "...");
	int* occurences = malloc((argc-1)*sizeof(int));
	check_error(occurences != NULL, "...");
	int currentMax = -1;
	
	for (int i = 0; i < argc - 1; i++) {
		occurences[i] = 0;
		fds[i].fd = open(argv[i+1], O_RDONLY | O_NONBLOCK);
		check_error(fds[i].fd != -1, "...");
		fds[i].events = POLLIN|POLLERR|POLLHUP;
		fds[i].revents=0;
	}
	
	int numOfActive = argc - 1;
	char buffer[BUF_SIZE];

	while (numOfActive) {
		
		int retVal = poll(fds, argc-1,-1);
		check_error(retVal != -1, "...");
		
		for (int i = 0; i<argc - 1; i++) {
			
			if (fds[i].revents & POLLIN) {
				int readBytes = 0;

				while ((readBytes = read(fds[i].fd, buffer, BUF_SIZE)) > 0) {
					
					for (int j=0; j<readBytes;j++) {
						if (buffer[j] == 'a') {
							occurences[i]++;
						}
					}
				}
				
				if (currentMax == -1 || occurences[i] > occurences[currentMax]) {
					
					currentMax = i;
				}
				
				if (readBytes == -1 && errno != EAGAIN) {
					check_error(readBytes != -1, "....");
				}
				
				fds[i].revents = 0;
			}
			else if (fds[i].revents & (POLLHUP | POLLERR)){
				
				
				close(fds[i].fd);
				fds[i].fd = -1;
				fds[i].events = 0;
				fds[i].revents = 0;
				numOfActive--;
			}
		}
	}
	
	char* pos = strrchr(argv[currentMax+1], '/');
	printf("%s %d\n", pos != NULL ? pos : argv[currentMax+1], occurences[currentMax]);
	
	free(fds);
	free(occurences);
	
	
	exit(EXIT_SUCCESS);
}
