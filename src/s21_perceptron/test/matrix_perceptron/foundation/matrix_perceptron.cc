//
// Created by Anton Ivanov on 04.05.2023.
//

#include <gtest/gtest.h>

#include "s21_matrix_perceptron.h"

#include <filesystem>

TEST(MatrixPerceptron, constructor_with_parameters) {

  // given
  std::filesystem::remove_all("test_constructor_with_parameters");
  auto parameters = s21::Perceptron::Parameters();
  parameters.number_of_layers = 5;
  parameters.number_of_neurons_in_layer = new int[5]{100, 500, 200, 64, 27};
  parameters.alpha = 0.05f;
  parameters.activation_name = "Sigmoid";
  auto input = Matrix(1, 100);

  // when
  auto returned = MatrixPerceptron(parameters);

  // then
  returned.ForwardPropagation(input);
  returned.ExportPerceptronToFile("perceptron_5_100_500_200_64_27", "test_constructor_with_parameters/");
}