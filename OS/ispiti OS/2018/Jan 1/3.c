#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
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
	
	osAssert(argc == 3, "Args");
	
	int pipes[2];
	osAssert(pipe(pipes) != -1, "pipe failed");
	
	if (strcmp(argv[2], "-w") && strcmp(argv[2], "-c") && strcmp(argv[2], "-l"))
		osAssert(false, "wrong option");
	
	pid_t childPid = fork();
	osAssert(childPid != -1, "fork failed");
	
	if (childPid > 0) {
		
		close(pipes[WR_END]);
		char* line = NULL;
		size_t bytesRead = 0;
		
		FILE* f = fdopen(pipes[RD_END], "r");
		osAssert(f != NULL, "fdopen failed");
		
		while (getline(&line, &bytesRead, f) != -1) {
			int num;
			sscanf(line, "%d", &num);
			printf("%d\n", num);
		}
		
		free(line);
		
		fclose(f);
	}
	else {
		close(pipes[RD_END]);
		
		osAssert(dup2(pipes[WR_END], STDOUT_FILENO) != -1, "dup2 failed");
		
		close(pipes[WR_END]);
		
		osAssert(execlp("wc", "wc", argv[1], argv[2], NULL) != -1, "exec failed");
	}
	
	int status = 0;
	osAssert(wait(&status) != -1, "wait failed");
	
	if (WIFEXITED(status)) {
		if (WEXITSTATUS(status) == EXIT_SUCCESS) {
			
		}
		else {
			printf("Neuspeh\n");
		}
	}
	else {
		printf("Neuspeh\n");
	}
	
	exit(EXIT_SUCCESS);

}
