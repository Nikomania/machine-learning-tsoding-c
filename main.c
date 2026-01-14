#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define IS_RANDOM 1
#define MAX_TRAINS 1000

float train[][2] = {
  {0, 0},
  {1, 2},
  {2, 4},
  {3, 6},
  {4, 8},
  //{67, 134}
};
#define train_count sizeof(train) / sizeof(train[0])

float rand_float(void);
float cost(float w, float b);

int main() {
  #if IS_RANDOM
  srand(time(0));
  #else
  srand(69);
  #endif

  float w = rand_float()*10.0f;
  float b = rand_float()*5.0f;
  float eps = 1e-3;
  float learning_rate = 1e-3;
  for (size_t i = 0; i < MAX_TRAINS; ++i) {
    float c = cost(w, b);
    float dw = (cost(w + eps, b) - c) / eps;
    float db = (cost(w, b + eps) - c) / eps;
    w -= dw * learning_rate;
    b -= db * learning_rate;
  
    printf("cost = %f, model = (%f, %f)\n", c, w, b);
  }

  printf("best model: (%f, %f)\n", w, b);

  return 0;
}

float rand_float(void) {
  return (float)rand() / (float) RAND_MAX;
}

float cost(float w, float b) {
  float result = 0.0f;
  for (size_t i = 0; i < train_count; ++i) {
    float x = train[i][0];
    float y = x * w + b;
    float y_train = train[i][1];

    float d = y - y_train;
    result += d * d;
  }
  result /= train_count;

  return result;
}
