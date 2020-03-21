#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <time.h>

#define check_error(expr, userMsg) \
	do { \
		if (!(expr)) {\
			perror(userMsg); \
			exit(EXIT_FAILURE); \
		}\
	} while(0)

int main(int argc, char** argv) {
	
	check_error(argc == 3, "Args");
	
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
	
	time_t rez = (time_t)(a + 60*b);
	struct tm* tm = localtime(&rez);
	check_error(tm != NULL, "...");
	
	char str[1204];
	strftime(str, 1024, "%d/%m/%Y %H:%M\n", tm);
	
	printf("%s", str);
	
	exit(EXIT_SUCCESS);
}
