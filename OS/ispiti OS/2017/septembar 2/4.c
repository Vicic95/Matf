#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define CHECK(expr, msg) \
    do { \
        if (!(expr)) { \
            perror(msg); \
            exit(1); \
        } \
    } while (0)

static const char *os_Months[] = {
	"januar", "februar", "mart", "april", "maj", "jun", "jul", 
	"avgust", "septembar", "oktobar", "novembar", "decembar"
};

int main(int argc, char const *argv[])
{
	CHECK(2 == argc, "Wrong cmd args num");
	time_t t = atol(argv[1]);
	struct tm *pT = localtime(&t);
	printf("%s\n", os_Months[pT->tm_mon]);
	return 0;
}