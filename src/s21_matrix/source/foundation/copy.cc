//
// Created by Anton Ivanov on 27.04.2023.
//

#include "s21_matrix.h"

void Matrix::copy(const Matrix& other) {

  auto size = other.m() * other.n();

  if (_m * _n < size) {

    if (_data != nullptr)
      delete[] _data;

    _data = new float[size];
  }

  _m = other.m();
  _n = other.n();

  auto other_data = other.data();

  for (auto i = 0; i < size; i++) {

    _data[i] = other_data[i];
  }
}
