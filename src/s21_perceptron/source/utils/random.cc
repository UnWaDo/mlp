//
// Created by Anton Ivanov on 03.05.2023.
//

#include "s21_utils.h"
#include <cmath>
#include <random>

Matrix s21::RandomMatrix(int m, int n) {

  auto size = m * n;
  auto data = new float[m * n];

  std::random_device r;
  std::mt19937 engine(r());
  std::uniform_real_distribution<float> distr(-1.0, 1.1);

  for(auto i(0); i < size; i += 1) {

    data[i] = distr(engine);
  }

  return {m, n, data};
}
