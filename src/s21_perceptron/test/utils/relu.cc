//
// Created by Anton Ivanov on 30.04.2023.
//

#include <gtest/gtest.h>

#include "s21_utils.h"

#define ABS_ERROR 1e-6f

TEST(Utils, relu_where_is_less_than_zero) {

  // given
  auto value = -21.0f;
  auto exp = 0.0f;

  // when
  auto returned = s21::Relu(value);

  // then
  EXPECT_NEAR(exp, returned, ABS_ERROR);
}

TEST(Utils, relu_where_is_equal_to_zero) {

  // given
  auto value = 0.0f;
  auto exp = 0.0f;

  // when
  auto returned = s21::Relu(value);

  // then
  EXPECT_NEAR(exp, returned, ABS_ERROR);
}

TEST(Utils, relu_where_is_greater_than_zero) {

  // given
  auto value = 21.0f;
  auto exp = 21.0f;

  // when
  auto returned = s21::Relu(value);

  // then
  EXPECT_NEAR(exp, returned, ABS_ERROR);
}

TEST(Utils, relu_where_matrix) {

  // given
  auto value = Matrix(1, 3, new float[3]{-21.0f, 0.0f, 42.0f});
  auto exp = Matrix(1, 3, new float[3]{0.0f, 0.0f, 42.0f});

  // when
  auto returned = s21::Relu(value);

  // then
  EXPECT_EQ(exp, returned);
}

TEST(Utils, derived_relu_where_is_less_than_zero) {

  // given
  auto value = -21.0f;
  auto exp = 0.0f;

  // when
  auto returned = s21::DerivedRelu(value);

  // then
  EXPECT_NEAR(exp, returned, ABS_ERROR);
}

TEST(Utils, derived_relu_where_is_equal_to_zero) {

  // given
  auto value = 0.0f;
  auto exp = 1.0f;

  // when
  auto returned = s21::DerivedRelu(value);

  // then
  EXPECT_NEAR(exp, returned, ABS_ERROR);
}

TEST(Utils, derived_relu_where_is_greater_than_zero) {

  // given
  auto value = 21.0f;
  auto exp = 1.0f;

  // when
  auto returned = s21::DerivedRelu(value);

  // then
  EXPECT_NEAR(exp, returned, ABS_ERROR);
}

TEST(Utils, derived_relu_where_matrix) {

  // given
  auto value = Matrix(1, 3, new float[3]{-21.0f, 0.0f, 42.0f});
  auto exp = Matrix(1, 3, new float[3]{0.0f, 1.0f, 1.00f});

  // when
  auto returned = s21::DerivedRelu(value);

  // then
  EXPECT_EQ(exp, returned);
}
