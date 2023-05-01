//
// Created by Anton Ivanov on 27.04.2023.
//

#include "s21_matrix.h"

float* Matrix::operator[](int i) const {

  return _data + i * _n;
}

//float* Matrix::operator[](int i) const {
//
//  return _data + i * _n;
//}
//
//float& Matrix::operator[](int i) {
//
//  return _data[i];
//}

int Matrix::m() const {

  return _m;
}

int Matrix::n() const {

  return _n;
}

float* Matrix::data() const {

  return _data;
}
