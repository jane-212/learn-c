#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void quick_sort(int *, int, int);
void print_arr(int *, int);
void bubble_sort(int *, int);

int main() {
  int arr[30000];
  int length = sizeof(arr) / sizeof(arr[0]);
  int i;
  clock_t start, end;

  srand((unsigned)time(NULL));

  for (i = 0; i < length; i++) {
    arr[i] = rand() % 100;
  }

  /* printf("before sort:\n"); */
  /* print_arr(arr, length); */

  start = clock();
  quick_sort(arr, 0, length - 1);
  end = clock();

  printf("time cost of quick sort is: %ldms\n", end - start);
  /* printf("after quick sort:\n"); */
  /* print_arr(arr, length); */

  start = clock();
  bubble_sort(arr, length);
  end = clock();

  printf("time cost of bubble sort is: %ldms\n", end - start);
  /* printf("after bubble sort:\n"); */
  /* print_arr(arr, length); */

  return 0;
}

void print_arr(int *arr, int length) {
  int i;

  printf("arr: ");
  for (i = 0; i < length; i++) {
    printf("%d", arr[i]);
    if (i != length - 1) {
      printf(",");
    }
  }
  printf("\n");
}

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void bubble_sort(int *arr, int length) {
  if (NULL == arr) {
    return;
  }

  int i, j;

  for (i = 0; i < length - 1; i++) {
    for (j = length - 1; j > i; j--) {
      if (arr[j] < arr[j - 1]) {
        swap(arr + j, arr + j + 1);
      }
    }
  }
}

void quick_sort(int *arr, int start, int end) {
  if (NULL == arr) {
    return;
  }

  if (start >= end) {
    return;
  }

  int base = arr[start];
  int left = start;
  int right = end;

  while (left < right) {
    while (arr[right] >= base && left < right) {
      --right;
    }

    while (arr[left] <= base && left < right) {
      ++left;
    }

    swap(arr + left, arr + right);
  }

  swap(arr + start, arr + right);

  quick_sort(arr, start, right - 1);
  quick_sort(arr, right + 1, end);
}
