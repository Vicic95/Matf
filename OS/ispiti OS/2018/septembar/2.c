#define _GNU_SOURCE
#define XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/wait.h>

#define RD_END (0)
#define WR_END (1)

#define check_error(expr, userMsg) \
	do { \
		if (!(expr)) {\
			perror(userMsg); \
			exit(EXIT_FAILURE); \
		}\
	} while(0)

int main(int argc, char** argv) {
	
	check_error(argc > 1, "Args");
	int cld2par[2];
	
	check_error(pipe(cld2par) != -1, "...");
	
	int pid = fork();
	check_error(pid != -1, "...");
	
	
	if (pid > 0) { //parent
		
		close(cld2par[WR_END]);
		
		FILE* f = fdopen(cld2par[RD_END], "r");
		check_error(f != NULL, "...");
		
		char* line = NULL;
		size_t len = 0;
		int lines_read = 0;
		
		while (getline(&line, &len, f) != -1) {
			lines_read++;
		}
		
		free(line);
		fclose(f);
		
		int status = 0;
		check_error(wait(&status) != -1, "...");
		
		if (WIFEXITED(status) && (WEXITSTATUS(status) == EXIT_SUCCESS)) {
			
			printf("%d\n", lines_read);
		}
		else {
			
			printf("Neuspeh\n");
			exit(EXIT_FAILURE);
		}
		
	}
	else { // child
		
		char** array = NULL;
		int i = 0;
		close(cld2par[RD_END]);
		
		array = malloc(sizeof(char*)*(argc+1));
		check_error(array != NULL, "...");
		
		array[0] = strdup(argv[1]);
		check_error(array[0] != NULL, "...");
		
		for (i = 1; i < argc; i++) {
			array[i] = strdup(argv[i]);
			check_error(array[0] != NULL, "...");
		}
		array[i] = NULL;
		
		check_error(dup2(cld2par[WR_END], STDOUT_FILENO) != -1, "...");
		check_error(execvp(array[0], array+1) != -1, "...");
	}
	
	exit(EXIT_SUCCESS);
}
