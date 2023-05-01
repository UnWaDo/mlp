//
// Created by Anton Ivanov on 27.04.2023.
//

#include "s21_matrix.h"

Matrix Matrix::transpose() const {

  auto data = new float[_m * _n];

  for (auto i = 0; i < _n; i += 1) {
    for (auto j = 0; j < _m; j += 1) {
      data[i * _m + j] = _data[j * _n + i];
    }
  }

  return {_n, _m, data};
}
