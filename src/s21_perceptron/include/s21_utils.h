//
// Created by Anton Ivanov on 29.04.2023.
//

#ifndef CPP7_MLP_1_SRC_S21_PERCEPTRON_INCLUDE_S21_UTILS_H_
#define CPP7_MLP_1_SRC_S21_PERCEPTRON_INCLUDE_S21_UTILS_H_

#include "s21_matrix.h"

namespace s21 {

Matrix Relu(const Matrix&);
float Relu(float);
Matrix DerivedRelu(const Matrix&);
float DerivedRelu(float);

Matrix Sigmoid(const Matrix&);
float Sigmoid(float);
Matrix Softmax(const Matrix&);

}

#endif //CPP7_MLP_1_SRC_S21_PERCEPTRON_INCLUDE_S21_UTILS_H_
