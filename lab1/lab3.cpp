#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#define PERM S_IRUSR | S_IWUSR    //(见注1)
#define MAX_SEQUENCE 10

typedef struct {
  long fib_sequence[MAX_SEQUENCE];
  int sequence_size;
} shared_data;

void Cal_fibonacci(shared_data*);
int main()
{
    key_t shmid;
    shared_data *p_addr, *c_addr;
    pid_t pid;
    // if(argc != 2) {
    //     fprintf(stderr, "Usage:%s\n\a", argv[0]);
    //     exit(1);
    // }
    if( (shmid = shmget(IPC_PRIVATE, 1024, PERM)) == -1 )   { //(见注1)
        fprintf(stderr, "Create Share Memory Error:%s\n\a", strerror(errno));
        exit(1);
    }
    p_addr = (shared_data*)shmat(shmid, 0, 0);
    scanf("%d", &(p_addr->sequence_size));
    //memset(shared_memory, '\0', 1024);
    pid = fork();
    if(pid > 0) {
       wait(0);
       //print the fibonacci sequence
       for (int i = 0; i < p_addr->sequence_size; i++) {
         printf("%ld ", (p_addr->fib_sequence)[i]);
       }
       shmdt((void*)p_addr);
       shmctl(shmid, IPC_PRIVATE, 0);
       exit(0);
    }
    else if (pid == 0){
       sleep(1);
       c_addr = (shared_data*)shmat(shmid, 0, 0);
       Cal_fibonacci(c_addr);
       shmdt((void*)p_addr);
       exit(0);
    }
}

void Cal_fibonacci(shared_data* data) {
  int fibonacci_factor = data->sequence_size;
  for (int i = 0; i < fibonacci_factor; i++) {
    if (i == 0) {
      (data->fib_sequence)[i] = 0;
    }
    else if (i == 1) {
      (data->fib_sequence)[i] = 1;
    }
    else {
      (data->fib_sequence)[i] = (data->fib_sequence)[i - 1] + (data->fib_sequence)[i - 2];
    }
  }
}
