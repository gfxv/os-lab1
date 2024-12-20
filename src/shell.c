#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT_SIZE 128
#define MAX_ARGS 16

void execute_command(char *input) {
  pid_t pid;
  int status;
  char *args[MAX_ARGS];
  char *token;
  time_t start_time, end_time;

  token = strtok(input, " \n");
  int i = 0;
  while (token != NULL && i < MAX_ARGS - 1) {
    args[i++] = token;
    token = strtok(NULL, " \n");
  }
  args[i] = NULL;

  start_time = time(NULL);
  pid = vfork();
  if (pid < 0) {
    perror("vfork failed");
    exit(1);
  } else if (pid == 0) {
    execvp(args[0], args);
    perror("exec failed");
    _exit(1);
  } else {
    waitpid(pid, &status, 0);
    end_time = time(NULL);
    if (WIFEXITED(status)) {
      printf("Program finished with exit status %d\n", WEXITSTATUS(status));
    }
    printf("Execution time: %lf seconds\n", (double) (end_time - start_time) / CLOCKS_PER_SEC);
  }
}

int main(void) {
  char input[MAX_INPUT_SIZE];

  while (1) {
    printf("cumass> ");
    if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
      break;
    }

    if (strlen(input) > 1) {
      execute_command(input);
    }
  }
  return 0;
}
