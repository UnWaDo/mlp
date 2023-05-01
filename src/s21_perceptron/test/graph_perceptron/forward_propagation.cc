//
// Created by Anton Ivanov on 29.04.2023.
//

#include <gtest/gtest.h>

#include "s21_matrix_perceptron.h"

TEST(GraphPerceptron, ForwardPropagation1) {

  // given
  auto input = Matrix(1, 2, new float[2] {2.0f, 3.0f});
  auto sut = MatrixPerceptron("perceptron_3_2_2_1", "resource/");
  auto exp = Matrix(1, 1, new float[1]{0.21f});

  // when
  auto returned = sut.ForwardPropagation(input);

  // then
  EXPECT_EQ(exp, returned);
}

TEST(GraphPerceptron, ForwardPropagation_where_two1) {

  // given
  auto input = Matrix(1, 32, new float[32] {0.86f, 0.05f, 0.1f,
      0.06f, 0.31f, 0.26f, 0.42f, 0.56f, 0.50f, 0.22f, 0.02f, 0.18f, 0.96f,
      0.23f, 0.52f, 0.95f, 0.46f, 0.19f, 0.84f, 0.91f, 0.38f, 0.92f, 0.53f,
      0.58f, 0.74f, 0.89f, 0.35f, 0.41f, 0.56f, 0.42f, 0.01f, 0.46f});
  auto sut = MatrixPerceptron("perceptron_3_32_128_4", "resource/");
  auto exp = Matrix(1, 4, new float[4]{512.69f, 486.03f, 472.04f, 494.63f});

  // when
  auto returned = sut.ForwardPropagation(input);

  // then
  EXPECT_EQ(exp, returned);
}
