//
// Created by Anton Ivanov on 29.04.2023.
//

#include <gtest/gtest.h>

#include "s21_utils.h"

TEST(Utils, softmax) {

  // given
  auto matrix = Matrix(5, 1, new float[5]{5.2f, 2.7f, 7.1f, 8.3f, 1.9f});
  auto exp = Matrix(5, 1, new float[5]{
      0.033330f,
      0.002736f,
      0.222842f,
      0.739862f,
      0.001229f});

  // when
  auto returned = s21::Softmax(matrix);

  // then
  EXPECT_EQ(exp, returned);
}
