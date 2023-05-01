//
// Created by Anton Ivanov on 27.04.2023.
//

#include "s21_matrix.h"

void Matrix::copy(const Matrix& other) {

  _m = other.m();
  _n = other.n();
  _data = new float[_m * _n];

  auto other_data = other.data();

  for (auto i = 0; i < _m; i += 1) {
    for (auto j = 0; j < _n; j += 1) {
      _data[i * _n + j] = other_data[i * _n + j];
    }
  }
}
