//
// Created by Anton Ivanov on 18.03.2023.
//

#include <cassert>

#include "s21_matrix.h"

namespace s21 {

Matrix::Matrix() : _m(0), _n(0), _data(nullptr) {}

Matrix::Matrix(int m, int n) : _m(m), _n(n), _data(new float[m * n]) {}

Matrix::Matrix(int m, int n, float *data) : _m(m), _n(n), _data(data) {}

Matrix::Matrix(const Matrix &other) : Matrix() {

  copy(other);
}

Matrix::~Matrix() {

  if (_data != nullptr)
    delete[] _data;
}
}
