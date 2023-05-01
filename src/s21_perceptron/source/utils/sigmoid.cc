//
// Created by Anton Ivanov on 29.04.2023.
//

#include "s21_utils.h"
#include <cmath>

Matrix s21::Sigmoid(const Matrix& t) {

  auto c = Matrix(t.m(), t.n());

  for (auto i(0); i < t.n(); i += 1) {

    c[0][i] = Sigmoid(t[0][i]);
  }

  return c;
}

float s21::Sigmoid(float value) {

  return 1 / (1 + exp(-value));
}
