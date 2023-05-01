//
// Created by Anton Ivanov on 28.04.2023.
//

#include <gtest/gtest.h>

#include "s21_matrix.h"

TEST(Matrix, get) {

  // given
  auto sut = Matrix(3, 3, new float[9]{5, 0, 0, 1, 9, 8, 6, 4, 3});
  auto j = 2;
  auto i = 1;
  auto exp = 8;

  // when
  auto returned = sut[i][j];

  // then
  EXPECT_EQ(exp, returned);
}

TEST(Matrix, set) {

  // given
  auto sut = Matrix(3, 3, new float[9]{5, 0, 0, 1, 9, 8, 6, 4, 3});
  auto i = 1;
  auto j = 2;
  auto value = 24.f;
  auto exp = Matrix(3, 3, new float[9]{5, 0, 0, 1, 9, 24, 6, 4, 3});

  // when
  sut[i][j] = value;

  // then
  EXPECT_EQ(exp, sut);
}
