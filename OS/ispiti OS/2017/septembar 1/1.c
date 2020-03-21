#define _GNU_SOURCE

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

#define MAX_WORD_SIZE (64)

#define CHECK(cond, msg) \
    do{ \
        if (!(cond)) { \
            perror((msg)); \
            exit(EXIT_FAILURE); \
        } \
    } while (false)
    
int os_WhichSignal = 0;

void osHandleSignal(int signum) {
  os_WhichSignal = signum;
}

void printBackwards(const char *s, FILE *stream) {
  int n = strlen(s);
  while (n--) fprintf(stream, "%c", s[n]);
  fprintf(stream, "\n");
}

void printUpper(const char *s, FILE *stream) {
  while (*s) fprintf(stream, "%c", toupper(*s++));
  fprintf(stream, "\n");
}

int main() {
    CHECK(SIG_ERR != signal(SIGUSR1, osHandleSignal), "SIGUSR1 handler failed to set");
    CHECK(SIG_ERR != signal(SIGUSR2, osHandleSignal), "SIGUSR2 handler failed to set");
    CHECK(SIG_ERR != signal(SIGTERM, osHandleSignal), "SIGTERM handler failed to set");
    fprintf(stderr, "PID=%jd\n", (intmax_t)getpid());
    
    char word[MAX_WORD_SIZE];
    while (true) {
        scanf("%s", word);
        pause();
        if (SIGUSR1 == os_WhichSignal) 
          printBackwards(word, stdout);
        else if (SIGUSR2 == os_WhichSignal)
          printUpper(word, stdout);
        else if (SIGTERM == os_WhichSignal)
          exit(0);
    }
    return 0;
}
