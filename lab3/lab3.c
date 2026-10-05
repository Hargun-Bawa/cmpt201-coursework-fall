#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#define SIZE 1000

void print_thing(char **l, ssize_t v) {
  for (int i = 0; i < 5; i++) {
    if (strlen(l[(v + i) % 5]) > 0) {
      printf("%lu, %s", strlen(l[(v + i + 1) % 5]), (l[(v + i + 1) % 5]));
    }
  }
};
int main() {
  char a[SIZE];
  char b[SIZE];
  char c[SIZE];
  char d[SIZE];
  char e[SIZE];
  char *list[5] = {a, b, c, d, e};

  int counter = 0;
  while (1 == 1) {

    size_t len = 1000;
    int id = counter % 5;
    size_t g = getline(&(list[id]), &len, stdin);
    if (g == 0) {
      list[id][0] = '\n';
    }
    if (g < 1) {
      perror("GETLINE");
      exit(1);
    }
    if (g >= strlen("print")) {
      if (strncmp(list[id], "print\0", g - 1) == 0) {
        print_thing(list, counter);
      }
    }
    counter++;
  }
}
