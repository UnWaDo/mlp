//
// Created by Anton Ivanov on 29.04.2023.
//

#include "s21_graph_perceptron.h"

void GraphPerceptron::BackPropagation(const Matrix& x, const Matrix& t) {

  (void)x;
  (void)t;
//  auto size = _number_of_layers - 3;
//
//  auto y = ForwardPropagation(x);
//
//  auto dE_dh = Matrix();
//  auto dE_dt = y - t;
//
//  _dE_dW[size + 1] = _h[size].transpose() * dE_dt;
//  _dE_db[size + 1] = dE_dt;
//
//  for (auto i(size); i > 0; i -= 1) {
//
//    dE_dh = dE_dt * _W[i + 1].transpose();
//    dE_dt = Matrix::multiply(dE_dh, _derivedActivation(_t[i]));
//
//    _dE_dW[i] = _h[i - 1].transpose() * dE_dt;
//    _dE_db[i] = dE_dt;
//  }
//
//  dE_dh = dE_dt * _W[1].transpose();
//  dE_dt = Matrix::multiply(dE_dh, _derivedActivation(_t[0]));
//
//  _dE_dW[0] = x.transpose() * dE_dt;
//  _dE_db[0] = dE_dt;

  update();
}

void GraphPerceptron::update() {

//  for (auto i(0); i < _number_of_layers - 1; i += 1) {
//
//    _W[i] = _W[i] - _dE_dW[i] * _alpha;
//    _b[i] = _b[i] - _dE_db[i] * _alpha;
//  }
}
