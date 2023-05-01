//
// Created by Anton Ivanov on 18.03.2023.
//

#include <cassert>

#include "s21_matrix.h"

Matrix::Matrix() = default;

Matrix::Matrix(int m, int n): _m(m), _n(n), _data(new float[m * n]) { }

Matrix::Matrix(int m, int n, float* data): _m(m), _n(n), _data(data) { }

Matrix::Matrix(const Matrix& other) {

  copy(other);
}

Matrix::~Matrix() {

  delete[] _data;
}
