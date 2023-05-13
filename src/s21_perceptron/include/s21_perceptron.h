//
// Created by Anton Ivanov on 29.04.2023.
//

#ifndef CPP7_MLP_1_SRC_S21_PERCEPTRON_INCLUDE_S21_PERCEPTRON_H_
#define CPP7_MLP_1_SRC_S21_PERCEPTRON_INCLUDE_S21_PERCEPTRON_H_

#include "s21_matrix.h"

namespace s21 {

class Perceptron {
 public:

  struct Parameters {
    int number_of_layers;
    int* number_of_neurons_in_layer;
    float alpha;
    std::string activation_name;
  };

  virtual ~Perceptron() {};

  virtual Matrix ForwardPropagation(const Matrix& input) = 0;

  virtual void BackPropagation(const Matrix& x, const Matrix& t) = 0;

  virtual void ExportPerceptronToFile(const std::string& name,
                                      const std::string& path = "./") = 0;
};
}

using namespace s21;

#endif //CPP7_MLP_1_SRC_S21_PERCEPTRON_INCLUDE_S21_PERCEPTRON_H_
