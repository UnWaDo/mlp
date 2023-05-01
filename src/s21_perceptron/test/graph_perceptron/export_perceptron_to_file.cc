//
// Created by Anton Ivanov on 30.04.2023.
//

#include <gtest/gtest.h>

#include "s21_graph_perceptron.h"

TEST(GraphPerceptron, ExportPerceptronToFile1) {

  // given
//  auto x = Matrix(1, 2, new float[2]{2.0f, 3.0f});
//  auto t = Matrix(1, 1, new float[1]{1.0f});
  auto sut = GraphPerceptron("perceptron_3_2_2_1", "resource/");
//  auto exp = Matrix(1, 1, new float[1]{0.32185965f});

  // when
  sut.ExportPerceptronToFile("дlol");

  // then
//  auto returned =  sut.ForwardPropagation(x);
//  EXPECT_EQ(exp, returned);
}
