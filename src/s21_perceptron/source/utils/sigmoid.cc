//
// Created by Anton Ivanov on 29.04.2023.
//

#include "s21_utils.h"
#include <cmath>

Matrix s21::Sigmoid(const Matrix& matrix) {

  assert(matrix.m() == 1);

  auto n = matrix.n();
  auto matrix_data = matrix.data();

  auto data = new float[n];

  for (auto j(0); j < n; j += 1) {

    data[j] = Sigmoid(matrix_data[j]);
  }

  return {1, n, data};
}

Matrix s21::DerivedSigmoid(const Matrix& matrix) {

  assert(matrix.m() == 1);

  auto n = matrix.n();
  auto matrix_data = matrix.data();

  auto data = new float[n];

  for (auto j(0); j < n; j += 1) {

    data[j] = DerivedSigmoid(matrix_data[j]);
  }

  return {1, n, data};
}

float s21::Sigmoid(float value) {

  return 1 / (1 + exp(-value));
}

float s21::DerivedSigmoid(float value) {

  auto result = Sigmoid(value);
  return result * (1 - result);
}
