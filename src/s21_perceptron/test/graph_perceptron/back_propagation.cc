//
// Created by Anton Ivanov on 30.04.2023.
//

#include <gtest/gtest.h>

#include "s21_matrix_perceptron.h"

TEST(GraphPerceptron, BackPropagation1) {

  // given
  auto x = Matrix(1, 2, new float[2]{2.0f, 3.0f});
  auto t = Matrix(1, 1, new float[1]{1.0f});
  auto sut = MatrixPerceptron("perceptron_3_2_2_1", "resource/");
  auto exp = Matrix(1, 1, new float[1]{0.32185965f});

  // when
  sut.BackPropagation(x, t);

  // then
  auto returned = sut.ForwardPropagation(x);
  EXPECT_EQ(exp, returned);
}

TEST(GraphPerceptron, BackPropagation_two1) {

  // given
  auto x = Matrix(1, 64, new float[64]{0.22, 0.54, 0.85, 0.38,
      0.99, 0.41, 0.82, 0.39, 0.51, 0.84, 0.84, 0.67, 0.76, 0.67, 0.44, 0.62,
      0.90, 0.11, 0.18, 0.63, 0.96, 0.24, 0.53, 0.55, 0.52, 0.02, 0.12, 0.51,
      0.08, 0.59, 0.31, 0.37, 0.73, 0.19, 0.55, 0.62, 0.69, 0.51, 0.28, 1.00,
      0.54, 0.36, 0.20, 0.26, 0.23, 0.09, 0.96, 1.00, 0.02, 0.07, 0.45, 0.28,
      0.75, 0.03, 0.66, 0.7 , 0.25, 0.75, 0.55, 0.72, 0.6 , 0.91, 0.05, 0.54});
  auto t = Matrix(1, 10, new float[10]{0.87, 0.67, 0.64, 0.95,
      0.77, 0.35, 0.96, 0.74, 0.95, 0.56});
  auto sut = MatrixPerceptron("perceptron_4_64_30_12_10", "resource/");
  auto exp = Matrix(1, 10, new float[10]{-69.505417919, -73.146659585,
      -67.946376748, -84.217286672, -89.248463974, -79.222304315,
      -73.552763119, -81.205465789, -72.716457869, -74.455032899});

  // when
  sut.BackPropagation(x, t);

  // then
  auto returned = sut.ForwardPropagation(x);
  EXPECT_EQ(exp, returned);
}
