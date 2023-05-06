//
// Created by Anton Ivanov on 30.04.2023.
//

#include <gtest/gtest.h>

#include "s21_utils.h"

TEST(Utils, random_matrix_where_check_m) {

  // given
  auto m = 21;
  auto n = 42;
  auto exp = 21;

  // when
  auto returned = s21::RandomMatrix(m, n);

  // then
  EXPECT_EQ(exp, returned.m());
}

TEST(Utils, random_matrix_where_check_n) {

  // given
  auto m = 21;
  auto n = 42;
  auto exp = 42;

  // when
  auto returned = s21::RandomMatrix(m, n);

  // then
  EXPECT_EQ(exp, returned.n());
}
