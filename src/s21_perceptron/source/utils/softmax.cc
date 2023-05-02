//
// Created by Anton Ivanov on 29.04.2023.
//

#include "s21_utils.h"
#include <cmath>

Matrix s21::Softmax(const Matrix& matrix) {

  assert(matrix.m() == 1);

  auto n = matrix.n();
  auto matrix_data = matrix.data();

  auto data = new float[n];
  auto sum = 0.0f;

  for (auto j(0); j < n; j += 1) {

    data[j] = exp(matrix_data[j]);
    sum += data[j];
  }

  for (auto j(0); j < n; j += 1) {

    data[j] /= sum;
  }

  return {1, n, data};
}
