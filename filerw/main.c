#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *s;
  size_t maxSize;
} Str;

int append_str(Str *, const char *);
Str *new_str(const char *);
void delete_str(Str *);
void print_str(Str *);

int main() {
  FILE *fp = NULL;
  char buf[1024] = "";
  FILE *pp = NULL;

  Str *str = new_str("");
  if (NULL == str) {
    puts("failed to new str");
    exit(EXIT_FAILURE);
  }

  if (fopen_s(&fp, "text.txt", "r") != 0) {
    printf("failed to open test.txt\n");
    delete_str(str);
    exit(EXIT_FAILURE);
  }
  pp = _popen("ls -al", "r");
  if (NULL == pp) {
    printf("failed to open pipe\n");
    delete_str(str);
    if (fclose(fp)) {
      printf("failed to close test.txt\n");
      exit(EXIT_FAILURE);
    }
    exit(EXIT_FAILURE);
  }

  while (fgets(buf, sizeof(buf), pp) != NULL) {
    if (append_str(str, buf)) {
      puts("failed to append str");
      delete_str(str);
      if (fclose(fp)) {
        printf("failed to close test.txt\n");
        exit(EXIT_FAILURE);
      }
      if (_pclose(pp)) {
        printf("failed to close pipe\n");
        exit(EXIT_FAILURE);
      }
      exit(EXIT_FAILURE);
    }
  }

  if (fclose(fp)) {
    printf("failed to close test.txt\n");
    delete_str(str);
    exit(EXIT_FAILURE);
  }

  if (_pclose(pp)) {
    printf("failed to close pipe\n");
    exit(EXIT_FAILURE);
  }

  printf("before append_str:\n");

  print_str(str);
  printf("str maxsize is: %zu\n", str->maxSize);

  append_str(str, " append");

  printf("after append_str:\n");

  print_str(str);
  printf("str maxsize is: %zu\n", str->maxSize);

  delete_str(str);

  return 0;
}

void print_str(Str *str) { puts(str->s); }

Str *new_str(const char *s) {
  Str *str = (Str *)malloc(sizeof(Str));
  if (NULL == str) {
    return NULL;
  }

  str->maxSize = 1024;
  if (strlen(s) > str->maxSize) {
    str->maxSize = strlen(s);
  }
  str->s = (char *)malloc(sizeof(char) * (str->maxSize + 1));
  if (NULL == str->s) {
    return NULL;
  }
  strcpy_s(str->s, str->maxSize + 1, s);

  return str;
}

void delete_str(Str *str) {
  if (str->s != NULL) {
    free(str->s);
    str->s = NULL;
  }

  if (str != NULL) {
    free(str);
    str = NULL;
  }
}

int append_str(Str *str, const char *newStr) {
  while (strlen(str->s) + strlen(newStr) > str->maxSize) {
    str->maxSize *= 2;
    str->s = (char *)realloc(str->s, sizeof(char) * (str->maxSize + 1));
    if (NULL == str->s) {
      return -1;
    }
  }

  strcat_s(str->s, str->maxSize + 1, newStr);

  return 0;
}
