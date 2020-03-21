#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <sys/wait.h>
#include <string.h>

#define osAssert(expr,msg){\
    if(!(expr)){\
        perror(msg);\
        exit(EXIT_FAILURE);\
    }\
}while(0)
#define RD_END (0)
#define WR_END (1)		

int main(int argc, char** argv) {
	
	osAssert(argc == 2, "Args");
	
	int pipeFds[2];
	osAssert(pipe(pipeFds) != -1, "pipe failed");
	
	pid_t childPid = fork();
	osAssert(childPid != -1, "fork failed");
	
	int totalNum = 0;
	
	if (childPid > 0) { // parent
		
		close(pipeFds[WR_END]);
		
		size_t bufLen = 0;
		char* buf = NULL;
		
		FILE* stream = fdopen(pipeFds[RD_END], "r");
		osAssert(stream != NULL, "fdopen failed");
		
		while (getline(&buf, &bufLen, stream) != -1) {
			
			buf[strlen(buf) - 1] = 0;
			
			char* ext = strrchr(buf, '.');
			if (ext != NULL) {
				if (!strcmp(ext, argv[1])) {
					totalNum++;
				}
			}
		}
		
		printf("%d\n", totalNum);
		
		free(buf);
		fclose(stream);
	}
	else { // child
		
		close(pipeFds[RD_END]);
		
		osAssert(dup2(pipeFds[WR_END], STDOUT_FILENO) != -1, "dup2 failed");
		
		osAssert(execlp("find", "find", ".", "-type", "f", NULL) !=- 1, "Exec failed");
		
		exit(EXIT_FAILURE);
	}
	
	int status;
	osAssert(wait(&status) != -1, "wait failed");
	
	if (!WIFEXITED(status) || !(WEXITSTATUS(status) == EXIT_SUCCESS)) {
		printf("Neuspeh");
	}
	
	exit(EXIT_SUCCESS);
}
