//
// Created by Anton Ivanov on 29.04.2023.
//

#include "s21_matrix_perceptron.h"
#include "s21_utils.h"

Matrix MatrixPerceptron::ForwardPropagation(const Matrix& x) {

  _t[0] = x * _W[0];
  _t[0] += _b[0];
  _h[0] = _activation(_t[0]);

  for (auto i(0); i < _number_of_hidden_layers; i += 1) {

    _t[i + 1] = _h[i] * _W[i + 1];
    _t[i + 1] += _b[i + 1];
    _h[i + 1] = _activation(_t[i + 1]);
  }

  // auto last_layer = _number_of_hidden_layers - 1;
  // auto z = _h[last_layer] * _W[last_layer + 1] + _b[last_layer + 1];

//  return s21::Softmax(_h[_number_of_hidden_layers - 1]);
  return _h[_number_of_hidden_layers];
}
