#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define CHECK(cond, msg) \
    do{ \
        if (!(cond)) { \
            perror((msg)); \
            exit(EXIT_FAILURE); \
        } \
    } while (false)

const char *os_WeekDays[] = {
  "nedelja", "ponedeljak", "utorak", "sreda", "cetvrtak", "petak", "subota"
};

int main(int argc, char **argv) {
    CHECK(2 == argc, "Args");
    
    time_t seconds = (time_t)atol(argv[1]);
    struct tm *pHumanTime = localtime(&seconds);
    
    printf("%s\n", os_WeekDays[pHumanTime->tm_wday]);
    return 0;
}
