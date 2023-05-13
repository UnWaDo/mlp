//
// Created by Anton Ivanov on 29.04.2023.
//

#include <fstream>
#include <string>

#include "s21_matrix_perceptron.h"
#include "s21_utils.h"

MatrixPerceptron::MatrixPerceptron(const s21::Perceptron::Parameters& parameters) {

  _number_of_layers = parameters.number_of_layers;
  _number_of_hidden_layers = _number_of_layers > 2 ? _number_of_layers - 2 : 0;
  _number_of_neurons_in_layers = new int[_number_of_layers];

  for (auto i(0); i < _number_of_layers; i += 1) {

    _number_of_neurons_in_layers[i] = parameters.number_of_neurons_in_layer[i];
  }

  _alpha = parameters.alpha;

  _activation_name = parameters.activation_name;

  if (_activation_name == "Relu") {

    _activation = s21::Relu;
    _derivedActivation = s21::DerivedRelu;

  } else if (_activation_name == "Sigmoid") {

    _activation = s21::Sigmoid;
    _derivedActivation = s21::DerivedSigmoid;

  } else {

    throw "invalid_activation_name";
  }

  _W = new Matrix[_number_of_layers - 1];
  _b = new Matrix[_number_of_layers - 1];

  for (auto i(0); i < _number_of_layers - 1; i += 1) {

    _W[i] = s21::RandomMatrix(_number_of_neurons_in_layers[i], _number_of_neurons_in_layers[i + 1]);
    _b[i] = s21::RandomMatrix(1, _number_of_neurons_in_layers[i + 1]);
  }

  _h = new Matrix[_number_of_layers];
  _t = new Matrix[_number_of_layers];

  _dE_dW = new Matrix[_number_of_layers];
  _dE_db = new Matrix[_number_of_layers];
}

MatrixPerceptron::MatrixPerceptron(const std::string& name, const std::string& path) {

  auto bundle = path + name + "/";

  parse_info(bundle);

  _W = parse_layer(bundle, "weight.txt");
  _b = parse_layer(bundle, "bias.txt");

  _h = new Matrix[_number_of_layers - 1];
  _t = new Matrix[_number_of_layers - 1];

  _dE_dW = new Matrix[_number_of_layers - 1];
  _dE_db = new Matrix[_number_of_layers - 1];
}

void MatrixPerceptron::parse_info(const std::string& bundle) {

  auto path_filename = bundle + "info.txt";
  auto info_file = std::ifstream(path_filename);

  if (!info_file.is_open()) {

    throw "info_file_is_not_open";
  }

  info_file >> _number_of_layers;

  if (info_file.fail()) {

    throw "info_file_fail";
  }

  _number_of_hidden_layers = _number_of_layers > 2 ? _number_of_layers - 2 : 0;

  _number_of_neurons_in_layers = new int[_number_of_layers];

  for (auto i(0); i < _number_of_layers; i += 1) {

    info_file >> _number_of_neurons_in_layers[i];

    if (info_file.fail()) {

      throw "info_file_fail";
    }
  }

  info_file >> _alpha;
  info_file >> _activation_name;

  if (_activation_name == "Relu") {

    _activation = s21::Relu;
    _derivedActivation = s21::DerivedRelu;

  } else if (_activation_name == "Sigmoid") {

    _activation = s21::Sigmoid;
    _derivedActivation = s21::DerivedSigmoid;

  } else {

    throw "invalid_activation_name";
  }

  if (info_file.fail()) {

    throw "info_file_fail";
  }

  info_file.close();
}

Matrix* MatrixPerceptron::parse_layer(const std::string& bundle,
                                      const std::string& filename) const {

  auto array_of_matrices = new Matrix[_number_of_layers - 1];

  for (auto i(0); i < _number_of_layers - 1; i += 1) {

    auto path_filename = bundle + "layer_" + std::to_string(i + 1) + "_" + filename;
    auto some_file = std::ifstream(path_filename);

    if (!some_file.is_open()) {
      throw "some_file_is_not_open";
    }

    auto iterator_start = std::istreambuf_iterator<char>(some_file);
    auto iterator_end = std::istreambuf_iterator<char>();

    auto data = std::string(iterator_start, iterator_end);

    if (some_file.fail()) {
      throw "some_file_fail";
    }

    array_of_matrices[i] = Matrix::parse(data);

    some_file.close();
  }

  return array_of_matrices;
}

MatrixPerceptron::MatrixPerceptron(const MatrixPerceptron& other) {
  (void)other;
}

MatrixPerceptron::~MatrixPerceptron() {

  delete[] _number_of_neurons_in_layers;

  delete[] _W;
  delete[] _b;

  delete[] _h;
  delete[] _t;

  delete[] _dE_dW;
  delete[] _dE_db;
}
