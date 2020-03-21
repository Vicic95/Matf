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
    
int main(int argc, char **argv)
{
	CHECK(2 == argc, "Wrong cmd args num");

  int childToParent[2];
  CHECK(-1 != pipe(childToParent), "Creating childToParent pipe failed");
  pid_t pid = fork();
  CHECK(-1 != pid, "Fork-ing a child failed");
  
  if (IS_PARENT(pid))
  {
    close(childToParent[1]);
    
    FILE *stream = fdopen(childToParent[0], "r");
    CHECK(NULL != stream, "File opening failed");

    size_t n = 0;
    char *line = NULL;
    CHECK(-1 != getline(&line, &n, stream), "Failed when reading first line"); // ignore first line
    int lineLen;
    while (-1 != (lineLen = getline(&line, &n, stream)))
    {
      char *eightCol = malloc(lineLen);
      CHECK(NULL != eightCol, "Allocating word failed");
      sscanf(line, "%*s%*s%*s%*s%*s%*s%*s%s", eightCol);
      printf("%s\n", eightCol);
      free(eightCol);
    }
    
    fclose(stream);
    CHECK(-1 != wait(NULL), "Waiting on process failed");
  }
  else 
  {
    close(childToParent[0]);
    CHECK(-1 != dup2(childToParent[1], STDOUT_FILENO), "Redirection failed");
    CHECK(-1 != execlp("ls", "ls", "-l", argv[1], NULL), "Exec failed");
  }
  return 0;
}
