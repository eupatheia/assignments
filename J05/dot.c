#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 100000

struct thread_data {
  int start_index;
  int end_index;
  int * array1;
  int * array2;
  int dotproduct;
};

void * find_dot(void * userdata) {
  struct thread_data * data = (struct thread_data *) userdata;
  for (int i = data->start_index; i < data->end_index; i++) {
    data->dotproduct += data->array1[i] * data->array2[i];
  }
  return (void *) NULL;
}

int main(int argc, char *argv[]) {
  srand(time(0));

  int v[SIZE];
  int u[SIZE];
  int dotproduct = 0;

  for (int i = 0; i < SIZE; i++) {
    v[i] = rand() % 1000 - 500;
    u[i] = rand() % 1000 - 500;
    dotproduct += u[i] * v[i];
  }
  printf("Ground truth dot product: %d\n", dotproduct);

  pthread_t threads[4];
  struct thread_data data[4];
  int subsize = SIZE / 4;
  for (int i = 0; i < 4; i++) {
    data[i].start_index = subsize * i;
    data[i].end_index = subsize * (i + 1);
    data[i].array1 = v;
    data[i].array2 = u;
    data[i].dotproduct = 0;
    pthread_create(&threads[i], NULL, find_dot, (void *) &data[i]);
  }

  int final_dotproduct = 0;
  for (int i = 0; i < 4; i++) {
    pthread_join(threads[i], NULL);
    final_dotproduct += data[i].dotproduct;
  }

  printf("Test with 4 threads\n");
  printf("Answer with threads: %d\n", final_dotproduct);

  return 0;
}
