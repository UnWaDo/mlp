//
// Created by Anton Ivanov on 27.04.2023.
//

#include "s21_matrix.h"

Matrix Matrix::operator*(float value) const {

  auto data = new float[_m * _n];

  for (auto i(0); i < _m; i += 1) {
    for (auto j(0); j < _n; j += 1) {
      data[i * _n + j] = _data[i * _n + j] * value;
    }
  }

  return {_m, _n, data};
}

Matrix Matrix::operator*(const Matrix& other) const {

  assert(_n == other.m());

  auto m = _m;
  auto n = other.n();
  auto other_data = other.data();

  auto data = new float[m * n];

  for (auto i(0); i < m; i += 1) {

    for (auto j(0); j < n; j += 1) {

      data[i * n + j] = 0;
      for (auto k(0); k < _n; k += 1) {

        data[i * n + j] += _data[i * _n + k] * other_data[k * n + j];
      }
    }
  }

  return {m, n, data};
}

Matrix Matrix::operator+(const Matrix& other) const {

  assert(_m == other.m());
  assert(_n == other.n());

  auto other_data = other.data();

  auto data = new float[_m * _n];

  for (auto i(0); i < _m; i += 1) {
    for (auto j(0); j < _n; j += 1) {
      data[i * _n + j] = _data[i * _n + j] + other_data[i * _n + j];
    }
  }

  return {_m, _n, data};
}

Matrix Matrix::operator-(const Matrix& other) const {

  assert(_m == other.m());
  assert(_n == other.n());

  auto other_data = other.data();

  auto data = new float[_m * _n];

  for (auto i(0); i < _m; i += 1) {
    for (auto j(0); j < _n; j += 1) {
      data[i * _n + j] = _data[i * _n + j] - other_data[i * _n + j];
    }
  }

  return {_m, _n, data};
}
