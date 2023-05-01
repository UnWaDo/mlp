//
// Created by Anton Ivanov on 29.04.2023.
//

#include "s21_utils.h"
#include <cmath>

Matrix s21::Softmax(const Matrix& a) {

  auto n = a.m();
  auto c = Matrix(a.m(), n);
  auto sum = 0.0f;

  for (auto i(0); i < n; i += 1) {

    c[0][i] = exp(a[0][i]);
    sum += c[0][i];
  }

  for (auto i(0); i < n; i += 1) {

    c[0][i] /= sum;
  }

  return c;
}
