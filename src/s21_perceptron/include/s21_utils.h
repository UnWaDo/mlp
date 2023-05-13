//
// Created by Anton Ivanov on 29.04.2023.
//

#ifndef CPP7_MLP_1_SRC_S21_PERCEPTRON_INCLUDE_S21_UTILS_H_
#define CPP7_MLP_1_SRC_S21_PERCEPTRON_INCLUDE_S21_UTILS_H_

#include "s21_matrix.h"

namespace s21 {

Matrix RandomMatrix(int m, int n);

Matrix Relu(const Matrix&);
Matrix DerivedRelu(const Matrix&);
float Relu(float);
float DerivedRelu(float);

Matrix Sigmoid(const Matrix&);
Matrix DerivedSigmoid(const Matrix&);
float Sigmoid(float);
float DerivedSigmoid(float);

Matrix Softmax(const Matrix&);

}

using namespace s21;

#endif //CPP7_MLP_1_SRC_S21_PERCEPTRON_INCLUDE_S21_UTILS_H_
