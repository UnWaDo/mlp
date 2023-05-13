//
// Created by Anton Ivanov on 29.04.2023.
//

#include <fstream>
#include <string>

#include "s21_graph_perceptron.h"
#include "s21_utils.h"

GraphPerceptron::GraphPerceptron(const s21::Perceptron::Parameters& parameters) {

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

  for (auto i(0); i < _number_of_layers - 1; i += 1) {

    auto weight = s21::RandomMatrix(_number_of_neurons_in_layers[i], _number_of_neurons_in_layers[i + 1]);
    auto bias = s21::RandomMatrix(1, _number_of_neurons_in_layers[i + 1]);

    auto* layer = new Layer(weight, bias);

    if (layers_) {

      layers_->get_last_layer()->next = layer;

    } else {

      layers_ = layer;
    }
}
}

GraphPerceptron::GraphPerceptron(const std::string& name, const std::string& path) {

  auto bundle = path + name + "/";

  parse_info(bundle);
  parse_layer(bundle);
  _W = parse_layer(bundle, "weight.txt");
  _b = parse_layer(bundle, "bias.txt");
}

void GraphPerceptron::parse_info(const std::string& bundle) {

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

  if (info_file.fail()) {

    throw "info_file_fail";
  }

  info_file >> _activation_name;

  if (info_file.fail()) {

    throw "info_file_fail";
  }

  if (_activation_name == "Relu") {

    _activation = s21::Relu;
    _derivedActivation = s21::DerivedRelu;

  } else if (_activation_name == "Sigmoid") {

    _activation = s21::Sigmoid;
    _derivedActivation = s21::DerivedSigmoid;

  } else {

    throw "invalid_activation_name";
  }

  info_file.close();
}

void GraphPerceptron::parse_layer(const std::string& bundle) {

  for (auto i(0); i < _number_of_layers - 1; i += 1) {

    auto path = bundle + "layer_" + std::to_string(i + 1);

    auto weight_file = std::ifstream(path + "_" + "weight.txt");
    auto bias_file = std::ifstream(path + "_" + "bias.txt");

    if (!weight_file.is_open() || !bias_file.is_open()) {
      throw "weight_file_is_not_open_or_bias_file_is_not_open";
    }

    auto weight_iterator_start = std::istreambuf_iterator<char>(weight_file);
    auto weight_iterator_end = std::istreambuf_iterator<char>();
    auto weight_data = std::string(weight_iterator_start, weight_iterator_end);

    auto bias_iterator_start = std::istreambuf_iterator<char>(bias_file);
    auto bias_iterator_end = std::istreambuf_iterator<char>();
    auto bias_data = std::string(bias_iterator_start, bias_iterator_end);

    if (weight_file.fail() || bias_file.fail()) {
      throw "weight_file_fail_or_bias_file_fail";
    }

    auto weight = Matrix::parse(weight_data);
    auto bias = Matrix::parse(bias_data);

    weight_file.close();
    bias_file.close();

    auto* layer = new Layer(weight, bias);

    if (layers_) {

      layers_->get_last_layer()->next = layer;

    } else {

      layers_ = layer;
    }
  }
}

Matrix* GraphPerceptron::parse_layer(const std::string& bundle,
                                      const std::string& filename) const {

  auto array_of_matrices = new Matrix[_number_of_layers];

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

Perceptron::Parameters GraphPerceptron::GetParameters() const {

  auto parameters = Parameters();

  parameters.number_of_layers = _number_of_layers;
  parameters.number_of_neurons_in_layer = new int[_number_of_layers];
  parameters.alpha = _alpha;
  parameters.activation_name = _activation_name;

  for (auto i(0); i < _number_of_layers; i += 1) {
    parameters.number_of_neurons_in_layer[i] = _number_of_neurons_in_layers[i];
  }

  return parameters;
}
