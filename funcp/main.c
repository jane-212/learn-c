#include <stdio.h>

int sum(int, int );
int sub(int, int );
int calc(int (*)(int, int), int, int);

int main() {
  printf("Enter number a:\n");
  int a;
  scanf_s("%d", &a);
  
  printf("Enter number b:\n");
  int b;
  scanf_s("%d", &b);

  printf("a + b = %d\n", calc(sum, a, b));
  printf("a - b = %d\n", calc(sub, a, b));

  return 0;
}

int sum(int a, int b) {
  return a + b;
}

int sub(int a, int b) {
  return a - b;
}

int calc(int (*func)(int, int), int a, int b) {
  return func(a, b);
}

