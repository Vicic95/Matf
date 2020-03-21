#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define CHECK(expr, msg) \
    do { \
        if (!(expr)) { \
            perror(msg); \
            exit(1); \
        } \
    } while (0)

#define IS_PARENT(pid) ((pid) > 0)
    
int main()
{
  size_t n = 0;
  char *line = NULL;
  ssize_t charsInLine = 0;
  while(-1 != (charsInLine = getline(&line, &n, stdin)))
  {
    int childToParent[2];
    CHECK(-1 != pipe(childToParent), "Creating childToParent pipe failed");
    pid_t pid = fork();
    CHECK(-1 != pid, "Fork-ing a child failed");
    if (IS_PARENT(pid))
    {
      close(childToParent[1]);
      char result[16];
      int resultBytes = 0;
      CHECK((resultBytes = read(childToParent[0], result, sizeof result)), "Reading from child failed");
      close(childToParent[0]);
      CHECK(-1 != wait(NULL), "Waiting on process failed");

      result[resultBytes] = 0;
      printf("%s\n", result);
    }
    else 
    {
      close(childToParent[0]);
      CHECK(-1 != dup2(childToParent[1], STDOUT_FILENO), "Redirection failed");
      char op[3];
      char x[16];
      char y[16];
      sscanf(line, "%s%s%s", x, y, op);
      CHECK(-1 != execlp("expr", "expr", x, op, y, NULL), "Exec failed");
    }
  }
  return 0;
}
