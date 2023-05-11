//
// Created by Anton Ivanov on 27.04.2023.
//

#include "s21_matrix.h"

void Matrix::transposed() {

  if (_m == 1 || _n == 1) {

    std::swap(_m, _n);
    return ;
  }

  auto data = _data;

  _data = new float[_m * _n];

  for (auto i(0); i < _n; i += 1) {
    for (auto j(0); j < _m; j += 1) {
      _data[i * _m + j] = data[j * _n + i];
    }
  }

  std::swap(_m, _n);

  delete[] data;
}
