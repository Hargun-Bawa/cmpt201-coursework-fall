#define _DEFAULT_SOURCE
#include <error.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define BUFF 2046
struct header {
  uint64_t size;
  struct header *next;
};

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUFF];
  ssize_t len = snprintf(buf, BUFF, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);
  if (len < 0) {
    perror("snprntrf");
  }
  write(STDOUT_FILENO, buf, len);
}
int main() {
  size_t size = 128 - sizeof(struct header);
  size_t hsize = sizeof(struct header);
  print_out("size = %u\n", &size, sizeof(size_t));
  print_out("hsize = %u\n", &hsize, sizeof(size_t));

  void *ptr = sbrk(256);
  void *npt = (void *)ptr + 128;
  struct header *t = (struct header *)ptr;
  struct header *n = (struct header *)npt;
  t->size = 128;
  t->next = NULL;
  print_out("t-> size: %d\n", &t->size, sizeof(uint64_t));
  print_out("t-> next: %p\n", &t->next, sizeof(t->next));
  n->next = t;
  n->size = 128;
  print_out("n->size %d\n", &n->size, sizeof(uint64_t));
  print_out("n->next %p\n", &n->next, sizeof(&t->next));

  void *a = (void *)t;
  void *b = (void *)n;
  a += sizeof(struct header);
  b += sizeof(struct header);

  memset(a, '0', size - 1);
  memset(b, '1', size);
  print_out("%s\n", &a, size - 1);
  print_out("%s\n", &b, size);

  print_out("block_1: address %p, ", &t, sizeof(&t));
  print_out("block_1: size%d, ", &t->size, sizeof(t->size));
  print_out("block_1: next%p, \n", &t->next, sizeof(t->next));
  write(STDOUT_FILENO, a, size - 1);

  print_out("\nblock_2: address %p, ", &n, sizeof(&n));
  print_out("block_2: size%d, ", &n->size, sizeof(n->size));
  print_out("block_2: next%p, \n", &n->next, sizeof(n->next));
  write(STDOUT_FILENO, (void *)n + 16, size);

  return 0;
}
