#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include <errno.h>
#include <sys/wait.h>


#define osAssert(expr,msg){\
    if(!(expr)){\
        perror(msg);\
        exit(EXIT_FAILURE);\
    }\
}while(0)

#define RD_END   (0)
#define WR_END 	 (1)
#define MAX_SIZE (8192)

int main(int argc, char** argv) {
	
	int pipeFds[2];
	
	osAssert(argc == 2, "Args");
	osAssert(pipe(pipeFds) != -1, "pipe failed");
	
	pid_t childPid = fork();
	osAssert(childPid != -1, "fork failed");
	
	if (childPid == 0) { // child
		
		close(pipeFds[RD_END]);
		dup2(pipeFds[WR_END], STDOUT_FILENO);		
		osAssert(execlp("stat", "stat", "--format=%s", argv[1], NULL) != -1, "exec failed");
	}
	
	close(pipeFds[WR_END]);
	char buffer[MAX_SIZE];
	osAssert(read(pipeFds[RD_END], buffer, MAX_SIZE) != -1, "read failed");
	
	close(pipeFds[RD_END]);
	
	int status = 0;
	osAssert(waitpid(childPid, &status, 0) != -1, "wait failed");
	
	if (!WIFEXITED(status) || WEXITSTATUS(status) != EXIT_SUCCESS) {
			printf("Neuspeh\n");
			return 0;
	}
	
	int size;
	sscanf(buffer, "%d", &size);
	printf("%d\n", size);
	
	exit(EXIT_SUCCESS);
}
