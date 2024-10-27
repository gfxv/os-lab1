#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// generate array with random values
void generate_array(int *arr, int size) {
  for (int i = 0; i < size; i++) {
    arr[i] = rand() % 1000;
  }
}

void quicksort(int *arr, int low, int high) {
  if (low < high) {
    int mid = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
      if (arr[j] < mid) {
        i++;
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    quicksort(arr, low, i);
    quicksort(arr, i + 2, high);
  }
}

void bubble_sort(int *arr, int size) {
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <arr_length> <repeats>\n", argv[0]);
    return 1;
  }

  int n = atoi(argv[1]);
  int repeats = atoi(argv[2]);
  int *arr = malloc(n * sizeof(int));

  clock_t start_total = clock();
  clock_t start;
  clock_t end;

  for (int r = 0; r < repeats; r++) {
    // test multiple sorting algorithms
    start = clock();
    generate_array(arr, n);
    quicksort(arr, 0, n - 1);
    end = clock();

    printf("[%d] Quicksort execution time: %lf seconds\n", r+1, (double) (end - start) / CLOCKS_PER_SEC);

    start = clock();
    generate_array(arr, n);
    bubble_sort(arr, n);
    end = clock();

    printf("[%d] Bubble sort execution time: %lf seconds\n", r+1, (double) (end - start) / CLOCKS_PER_SEC);
  }
  clock_t end_total = clock();

  free(arr);
  printf("\n");
  printf(">>> Total execution time: %lf seconds <<<\n\n", (double) (end_total - start_total) / CLOCKS_PER_SEC);

  return 0;
}