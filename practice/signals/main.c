#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void sig_handler_parent(int signum) { write(STDOUT_FILENO, "hehe\n", 5); }
void sig_handler_child(int signum) { raise(SIGINT); }

int main() {

  int counter = 0;

  while (counter < 3) {
    pid_t id = fork();

    if (id == 0) {
      struct sigaction handler;
      handler.sa_sigaction = (void *)sig_handler_child;
      handler.sa_flags = 0;
      sigemptyset(&handler.sa_mask);
      sigaction(9, &handler, NULL);

      sleep(1);
      exit(0);

    }

    else {
      struct sigaction handler;
      handler.sa_sigaction = (void *)sig_handler_parent;
      handler.sa_flags = 0;
      sigemptyset(&handler.sa_mask);
      sigaction(9, &handler, NULL);

      int stat = 0;
      waitpid(id, &stat, 0);
      if (stat == -1) {
        exit(EXIT_FAILURE);
      }
      if (WIFEXITED(stat)) {
        printf("HMM\n");
      }
      if (WIFSIGNALED(stat)) {
        printf("signaled by: %d", WTERMSIG(stat));
        counter += 1;
      }
    }
  }
}
