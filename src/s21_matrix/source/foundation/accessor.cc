//
// Created by Anton Ivanov on 27.04.2023.
//

#include "s21_matrix.h"

float* Matrix::operator[](int i) const {

  return _data + i * _n;
}

int Matrix::m() const {

  return _m;
}

int Matrix::n() const {

  return _n;
}

float* Matrix::data() const {

  return _data;
}
