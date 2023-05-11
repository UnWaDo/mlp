//
// Created by Anton Ivanov on 27.04.2023.
//

#include "s21_matrix.h"

Matrix Matrix::multiply(const Matrix& a, const Matrix& b) {

  assert(a.m() == b.m());
  assert(a.n() == b.n());

  auto m = a.m();
  auto n = a.n();
  auto data = new float[m * n];

  auto a_data = a.data();
  auto b_data = b.data();

  for (auto i(0); i < m; i += 1) {
    for (auto j(0); j < n; j += 1) {
      data[i * n + j] = a_data[i * n + j] * b_data[i * n + j];
    }
  }

  return {m, n, data};
}

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

Matrix& Matrix::operator*=(float v) {

  auto size = _m * _n;

  for (auto i(0); i < size; i += 1) {
      _data[i] *= v;
  }

  return *this;
}

Matrix& Matrix::operator+=(const Matrix &b) {
  assert(_m == b.m());
  assert(_n == b.n());

  auto size = _m * _n;
  auto b_data = b.data();

  for (auto i(0); i < size; i += 1) {
    _data[i] += b_data[i];
  }

  return *this;
}

Matrix& Matrix::operator-=(const Matrix &b) {

  assert(_m == b.m());
  assert(_n == b.n());

  auto size = _m * _n;
  auto b_data = b.data();

  for (auto i(0); i < size; i += 1) {
    _data[i] -= b_data[i];
  }

  return *this;
}
