#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <sys/wait.h>
#include <string.h>

#define xstr(a) str(a)
#define str(a) #a


#define osAssert(expr,msg){\
    if(!(expr)){\
        perror(msg);\
        exit(EXIT_FAILURE);\
    }\
}while(0)

#define RD_END (0)
#define WR_END (1)

int main(int argc, char** argv) {
	
	osAssert(argc == 1, xstr(__LINE__));
	
	int cld2par[2];
	osAssert(pipe(cld2par) != -1, xstr(__LINE__));
	
	pid_t pid = fork();
	osAssert(pid != -1, xstr(__LINE__));
	
	if (pid > 0) { // parent
		
		close(cld2par[WR_END]);
		char* line = NULL;
		size_t lineLen = 0;
		
		FILE* f = fdopen(cld2par[RD_END], "r");
		osAssert(f != NULL, xstr(__LINE__));
		
		char privileges[11];
		while (getline(&line, &lineLen, f) != -1) {
			sscanf(line, "%s", privileges);
			if (!strcmp(privileges + 7, "rwx"))
				printf("%s", strrchr(line, ' ')+1);
		}
		free(line);
		fclose(f);
	}
	else { // child
		
		close(cld2par[RD_END]);
		
		osAssert(dup2(cld2par[WR_END], STDOUT_FILENO) != -1, xstr(__LINE__));
		
		osAssert(execlp("ls", "ls","-l",NULL) != -1, xstr(__LINE__));
	}
	
	int status = 0;
	osAssert(wait(&status) != -1, xstr(__LINE__));
	
	if (!WIFEXITED(status) || !(WEXITSTATUS(status) == EXIT_SUCCESS)) {
		fprintf(stderr, "Stampao neuspeh...\n");
		printf("neuspeh\n");
		exit(WEXITSTATUS(status));
	}
	
	exit(EXIT_SUCCESS);
}
