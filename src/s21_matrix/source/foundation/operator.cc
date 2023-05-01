//
// Created by Anton Ivanov on 27.04.2023.
//

#include "s21_matrix.h"

std::ostream& operator<<(std::ostream& stream, const Matrix& matrix) {

  return stream << matrix.description();
}

Matrix& Matrix::operator=(const Matrix& other) {

  if (this != &other) {
    copy(other);
  }

  return *this;
}

bool Matrix::operator==(const Matrix& other) const {

  auto epsilon = 1e-6f;

  if (_m != other.m() || _n != other.n()) {
    return false;
  }

  auto other_data = other.data();

  for (auto i(0); i < _m; i += 1) {
    for (auto j(0); j < _n; j += 1) {
      if (abs(_data[i * _n + j] - other_data[i * _n + j]) > epsilon) {
        return false;
      }
    }
  }

  return true;
}
