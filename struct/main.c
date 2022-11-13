#include <stdio.h>

typedef struct {
  int x;
  int y;
} Point;

void print_point(Point *);

int main() {
  Point p = {1, 2};

  printf("first:\n");
  print_point(&p);

  p.x = 2;
  p.y = 3;

  printf("second:\n");
  print_point(&p);

  Point *pp = &p;
  printf("third:\n");
  print_point(pp);

  return 0;
}

void print_point(Point *p) { printf("point: x = %d, y = %d\n", p->x, p->y); }

