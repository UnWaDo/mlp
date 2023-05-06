//
// Created by Anton Ivanov on 29.04.2023.
//

#include "s21_matrix_perceptron.h"
#include <filesystem>
#include <fstream>

void MatrixPerceptron::ExportPerceptronToFile(const std::string& name,
                                              const std::string& path) {
  auto bundle = path + name + "/";

//  auto status = std::filesystem::create_directory(path);
//
//  if (!status) {
//    throw "lol";
//  }

  auto status = std::filesystem::create_directory(bundle);

  if (!status) {
    throw "lol";
  }

  export_info(bundle);
  export_layer(bundle, "weight.txt", _W);
  export_layer(bundle, "bias.txt", _b);
}

void MatrixPerceptron::export_info(const std::string& bundle) const {

  auto info_file = std::ofstream(bundle + "info.txt");

  if (!info_file.is_open()) {
    throw "lol";
  }

  info_file << _number_of_layers << "\n";

  for (auto i(0); i < _number_of_layers; i += 1) {
    info_file << _number_of_neurons_in_layers[i] << " ";
  }

  info_file << "\n";
  info_file << _alpha << "\n";
  info_file << _activation_name << "\n";

  info_file.close();
}
void MatrixPerceptron::export_layer(const std::string& bundle,
                                    const std::string& filename,
                                    const Matrix* matrix) const {

  for (auto i(0); i < _number_of_layers - 1; i += 1) {

    auto path_filename = bundle + "layer_" + std::to_string(i + 1) + "_" + filename;
    auto some_file = std::ofstream(path_filename);

    if (!some_file.is_open()) {
      throw "lol";
    }

    some_file << matrix[i].description("\n") << "\n";

    if (some_file.fail()) {
      throw "lol";
    }

    some_file.close();
  }
}
