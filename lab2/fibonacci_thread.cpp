#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_NUM 100

long fibonacci_array[MAX_NUM];
void *cal_fib(void* param);
int fib_num = 0;

int main() {
  //input number of fibonacci from keyboard
  scanf("%d", &fib_num);
  pthread_t tid[MAX_NUM];
  //create the thread using tid
  for (int i = 0; i < fib_num; i++)
    pthread_create(&tid[i], NULL, cal_fib, (void*)&i);
  //wait for the thread to exit
  for (int i = 0; i < fib_num; i++) {

    pthread_join(tid[i], NULL);
  }
  //print out the final result
  for (int i = 0; i < fib_num; i++)
    printf("%ld ", fibonacci_array[i]);
}

void* cal_fib(void* param) {
  int n = *(int*)(param);

  //printf("%d\n", n);
  if (n == 0)
    fibonacci_array[n] = 0;
  else if (n == 1)
    fibonacci_array[n] = 1;
  else
    fibonacci_array[n] = fibonacci_array[n - 1] + fibonacci_array[n - 2];
  //exit thread
  pthread_exit(0);
}
