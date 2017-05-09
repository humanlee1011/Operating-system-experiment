#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define M 3
#define K 2
#define N 3

int A[M][K] = { {1, 4}, {2, 5}, {3, 6} };
int B[K][N] = {{8, 7, 6}, {5, 4, 3}};
int C[M][N];

//structure for passing data to threads
struct node {
  int i;//row
  int j;//column
};

void* multiplication(void* data) {
  node *tempdata = (node*)data;
  int sum = 0;
  for (int i = 0; i < K; i++) {
    sum += A[tempdata->i][i] * B[i][tempdata->j];
  }
  //printf("%d %d %d\n",tempdata->i, tempdata->j, sum);
  C[tempdata->i][tempdata->j] = sum;
  pthread_exit(0);
}

int main() {
  pthread_t tid[15];
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      struct node* tempdata = (struct node*)malloc(sizeof(struct node));
      tempdata->i = i;
      tempdata->j = j;
      //printf("%d\n", tempdata->j);
      pthread_create(&tid[i * M + j + 1], NULL, multiplication, (void*)tempdata);
    }
  }
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      pthread_join(tid[i * M + j + 1], NULL);
    }
  }
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      printf("%d ", C[i][j]);
    }
    printf("\n");
  }
}
