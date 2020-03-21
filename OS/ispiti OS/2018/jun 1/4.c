#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <errno.h>


#define osAssert(expr,msg){\
    if(!(expr)){\
        perror(msg);\
        exit(EXIT_FAILURE);\
    }\
}while(0)

int main(int argc, char** argv) {
	
	osAssert(argc == 2, "Args");
	
	int fd = open(argv[1], O_RDWR);
	osAssert(fd != -1, "...");
	
	FILE* f = fdopen(fd, "r+");
	osAssert(f != NULL, "...");
	int success = 0;
	int failure = 0;
	char buffer[1024];
	while (fscanf(f, "%s", buffer) == 1) {
		
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence = SEEK_SET;
		lock.l_start = ftell(f);
		lock.l_len = -strlen(buffer);
		
		if (fcntl(fd, F_SETLK, &lock) == -1) {
			if (errno != EACCES && errno != EAGAIN) {
				osAssert(0, "...");
			}
			failure++;
			continue;
		}
		else {
			int n = strlen(buffer);
			char* s = malloc(n + 1);
			osAssert(s != NULL, "...");
			
			int k = 0;
			for (int i = n-1; i >= 0; i--){
				s[k++] = buffer[i];
			}
			s[k] = 0;
			fseek(f, -n, SEEK_CUR);
			fprintf(f, "%s", s);
			free(s);
			
			lock.l_type = F_UNLCK;
			osAssert(fcntl(fd, F_SETLK, &lock) != -1, "...");
			success++;
		}
	}
	
	osAssert(feof(f), "...");
	
	printf("%d %d\n", success, failure);
	
	fclose(f);
	
	exit(EXIT_SUCCESS);
}
