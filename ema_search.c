#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFFER_SIZE 1024

void find_substring(const char *buffer, const char *substring, int line_number) {
  const char *ptr = buffer;
  int position;

  while ((ptr = strstr(ptr, substring)) != NULL) {
    position = ptr - buffer;
    printf("Found substring at line %d, position %d\n", line_number, position);
    ptr++;
  }
}

int process_file(const char *filename, const char *substring) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    perror("Error opening file");
    return EXIT_FAILURE;
  }

  char buffer[BUFFER_SIZE];
  int line_number = 0;
  while (fgets(buffer, BUFFER_SIZE, file)) {
    line_number++;
    find_substring(buffer, substring, line_number);
  }
  fclose(file);

  return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
  if (argc < 4) {
    fprintf(stderr, "Usage: %s <filename> <substring> <repeats>\n", argv[0]);
    return EXIT_FAILURE;
  }

  const char *filename = argv[1];
  const char *substring = argv[2];
  size_t repeats = atoi(argv[3]);

  if (strlen(substring) > BUFFER_SIZE) {
    fprintf(stderr, "Substring is larger than buffer size");
  }

  clock_t total_start = clock();
  for (int r = 0; r < repeats; r++) {
    clock_t start = clock();
    if (process_file(filename, substring) != 0) {
      fprintf(stderr, "[%d] AHTUNG AHTUNG SOME ERROR OCCURRED\n", r);
    }
    printf("Execution time: %lf seconds\n\n", (double) (clock() - start) / CLOCKS_PER_SEC);
  }
  clock_t total_end = clock();

  printf("\n");
  printf(">>> Total execution time: %lf seconds <<<\n\n", (double) (total_end - total_start) / CLOCKS_PER_SEC);

  return EXIT_SUCCESS;
}
