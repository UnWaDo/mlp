//
// Created by Anton Ivanov on 03.05.2023.
//

#include "s21_utils.h"
#include <cmath>

Matrix s21::RandomMatrix(int m, int n) {

  auto size = m * n;
  auto data = new float[m * n];

  for(auto i(0); i < size; i += 1) {

    data[i] = static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX);
  }

  return {m, n, data};
}
