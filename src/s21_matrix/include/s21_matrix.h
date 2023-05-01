//
// Created by Anton Ivanov on 18.03.2023.
//

#ifndef CPP7_MLP_1_S21_MATRIX_H
#define CPP7_MLP_1_S21_MATRIX_H

#include <string>
#include <cassert>

class Matrix {
 public:

  // Считывает матрицу из строки с данными
  static Matrix parse(std::string);

  // Поэлементное умножение матриц
  static Matrix multiply(const Matrix&, const Matrix&);

  Matrix();
  Matrix(int m, int n);
  Matrix(int m, int n, float* data);
  Matrix(const Matrix&);

  ~Matrix();

  float* operator[](int) const;

  [[nodiscard]] int m() const;
  [[nodiscard]] int n() const;
  [[nodiscard]] float* data() const;

  Matrix& operator=(const Matrix&);
  bool operator==(const Matrix&) const;

  // Описание в виде матрицы
  [[nodiscard]] std::string description() const;
  [[nodiscard]] std::string description(const std::string& separator) const;

  void transposed();
  [[nodiscard]] Matrix transpose() const;

  Matrix operator*(float) const;
  Matrix operator*(const Matrix&) const;
  Matrix operator+(const Matrix&) const;
  Matrix operator-(const Matrix&) const;

 private:

  int _m;
  int _n;
  float* _data;

  void copy(const Matrix&);
};

std::ostream& operator<<(std::ostream&, const Matrix&);

#endif  // CPP7_MLP_1_S21_MATRIX_H
