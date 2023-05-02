//
// Created by Anton Ivanov on 29.04.2023.
//

#include <fstream>
#include <string>

#include "s21_matrix_perceptron.h"
#include "s21_utils.h"

MatrixPerceptron::MatrixPerceptron(const s21::Perceptron::Parameters& parameters) {
  (void)parameters;
}

MatrixPerceptron::MatrixPerceptron(const std::string& name, const std::string& path) {

  auto bundle = path + name + "/";

  parse_info(bundle);

  _W = parse_layer(bundle, "weight.txt");
  _b = parse_layer(bundle, "bias.txt");

  _h = new Matrix[_number_of_layers];
  _t = new Matrix[_number_of_layers];

  _dE_dW = new Matrix[_number_of_layers];
  _dE_db = new Matrix[_number_of_layers];
}

void MatrixPerceptron::parse_info(const std::string& bundle) {

  auto path_filename = bundle + "info.txt";
  auto info_file = std::ifstream(path_filename);

  if (!info_file.is_open()) {

    throw "lol";
  }

  info_file >> _number_of_layers;

  if (info_file.fail()) {

    throw "lol";
  }

  _number_of_hidden_layers = _number_of_layers > 2 ? _number_of_layers - 2 : 0;

  _number_of_neurons_in_layers = new int[_number_of_layers];

  for (auto i(0); i < _number_of_layers; i += 1) {

    info_file >> _number_of_neurons_in_layers[i];

    if (info_file.fail()) {

      throw "lol";
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

    throw "lol";
  }

  if (info_file.fail()) {

    throw "lol";
  }

  info_file.close();
}

Matrix* MatrixPerceptron::parse_layer(const std::string& bundle,
                                      const std::string& filename) const {

  auto array_of_matrices = new Matrix[_number_of_layers];

  for (auto i(0); i < _number_of_layers - 1; i += 1) {

    auto path_filename = bundle + "layer_" + std::to_string(i + 1) + "_" + filename;
    auto some_file = std::ifstream(path_filename);

    if (!some_file.is_open()) {
      throw "lol";
    }

    auto iterator_start = std::istreambuf_iterator<char>(some_file);
    auto iterator_end = std::istreambuf_iterator<char>();

    auto data = std::string(iterator_start, iterator_end);

    if (some_file.fail()) {
      throw "lol";
    }

    array_of_matrices[i] = Matrix::parse(data);

    some_file.close();
  }

  return array_of_matrices;
}

MatrixPerceptron::MatrixPerceptron(const MatrixPerceptron& other) {
  (void)other;
}
