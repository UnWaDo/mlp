//
// Created by Anton Ivanov on 29.04.2023.
//

#ifndef CPP7_MLP_1_SRC_S21_PERCEPTRON_INCLUDE_S21_MATRIX_PERCEPTRON_H_
#define CPP7_MLP_1_SRC_S21_PERCEPTRON_INCLUDE_S21_MATRIX_PERCEPTRON_H_

#include "s21_perceptron.h"

class MatrixPerceptron: public s21::Perceptron {
 public:

  MatrixPerceptron(const s21::Perceptron::Parameters&);
  MatrixPerceptron(const std::string& name, const std::string& path = "./");
  MatrixPerceptron(const MatrixPerceptron&);

  ~MatrixPerceptron();

  Matrix ForwardPropagation(const Matrix& input) override;

  void BackPropagation(const Matrix& x, const Matrix& t) override;

  void ExportPerceptronToFile(const std::string& name, const std::string& path = "./") override;

  Parameters GetParameters() const override;

 private:

  int _number_of_layers;
  int _number_of_hidden_layers;
  int* _number_of_neurons_in_layers;

  float _alpha;

  std::string _activation_name;
  Matrix (*_activation)(const Matrix&);
  Matrix (*_derivedActivation)(const Matrix&);

  Matrix* _W;
  Matrix* _b;

  Matrix* _t;
  Matrix* _h;

  Matrix* _dE_dW;
  Matrix* _dE_db;

  void parse_info(const std::string& bundle);
  [[nodiscard]] Matrix* parse_layer(const std::string& bundle,
                                    const std::string& filename) const;

  void export_info(const std::string& bundle) const;
  void export_layer(const std::string& bundle,
                    const std::string& filename,
                    const Matrix* matrix) const;

  void update();
};

#endif //CPP7_MLP_1_SRC_S21_PERCEPTRON_INCLUDE_S21_MATRIX_PERCEPTRON_H_
