#include <stdio.h>
#include <unistd.h>

int main() {
  int pid1 = fork();
  int pid2;
  if (pid1 > 0) {
    pid2 = fork();
  }
  if (pid1 > 0 && pid2 > 0)
    printf("a\n");//the parent process print a
  else if (pid1 == 0)
    printf("b\n");//the child process 1 print b
  else if (pid2 == 0)
    printf("c\n");//the child process 2 print c
}
