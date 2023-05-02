//
// Created by Anton Ivanov on 30.04.2023.
//

#include "s21_utils.h"
#include <cmath>

Matrix s21::Relu(const Matrix& matrix) {

  assert(matrix.m() == 1);

  auto n = matrix.n();
  auto matrix_data = matrix.data();

  auto data = new float[n];

  for (auto j(0); j < n; j += 1) {

    data[j] = Relu(matrix_data[j]);
  }

  return {1, n, data};
}

Matrix s21::DerivedRelu(const Matrix& matrix) {

  assert(matrix.m() == 1);

  auto n = matrix.n();
  auto matrix_data = matrix.data();

  auto data = new float[n];

  for (auto j(0); j < n; j += 1) {

    data[j] = DerivedRelu(matrix_data[j]);
  }

  return {1, n, data};
}

float s21::Relu(float value) {

  return value > 0 ? value : 0;
}

float s21::DerivedRelu(float value) {

  return value >= 0 ? 1 : 0;
}
