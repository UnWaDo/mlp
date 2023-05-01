//
// Created by Anton Ivanov on 01.05.2023.
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
