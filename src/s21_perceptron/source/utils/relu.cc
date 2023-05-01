//
// Created by Anton Ivanov on 30.04.2023.
//

#include "s21_utils.h"
#include <cmath>

Matrix s21::Relu(const Matrix& a) {

  auto c = Matrix(a.m(), a.n());

  for (auto i(0); i < a.n(); i += 1) {

    c[0][i] = Relu(a[0][i]);
  }

  return c;
}

float s21::Relu(float value) {

  return value > 0 ? value : 0;
}

Matrix s21::DerivedRelu(const Matrix& a) {

  auto c = Matrix(a.m(), a.n());

  for (auto i(0); i < a.n(); i += 1) {

    c[0][i] = DerivedRelu(a[0][i]);
  }

  return c;
}

float s21::DerivedRelu(float value) {

  return value >= 0 ? 1 : 0;
}
