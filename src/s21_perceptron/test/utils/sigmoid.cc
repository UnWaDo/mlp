//
// Created by Anton Ivanov on 29.04.2023.
//

#include <gtest/gtest.h>

#include "s21_utils.h"

#define ABS_ERROR 1e-6f

TEST(Utils, sigmoid_where_is_equal_to_minus_one) {

  // given
  auto value = -1.0f;
  auto exp = 0.268941f;

  // when
  auto returned = s21::Sigmoid(value);

  // then
  EXPECT_NEAR(exp, returned, ABS_ERROR);
}

TEST(Utils, sigmoid_where_is_equal_to_zero) {

  // given
  auto value = 0.0f;
  auto exp = 0.5f;

  // when
  auto returned = s21::Sigmoid(value);

  // then
  EXPECT_NEAR(exp, returned, ABS_ERROR);
}

TEST(Utils, sigmoid_where_is_equal_to_one) {

  // given
  auto value = 1.0f;
  auto exp = 0.731059f;

  // when
  auto returned = s21::Sigmoid(value);

  // then
  EXPECT_NEAR(exp, returned, ABS_ERROR);
}

TEST(Utils, sigmoid_where_matrix) {

  // given
  auto value = Matrix(1, 3, new float[3]{-1.0f, 0.0f, 1.0f});
  auto exp = Matrix(1, 3, new float[3]{0.268941f, 0.5f,  0.731059f});

  // when
  auto returned = s21::Sigmoid(value);

  // then
  EXPECT_EQ(exp, returned);
}

TEST(Utils, derived_sigmoid_where_is_equal_to_minus_one) {

  // given
  auto value = -1.0f;
  auto exp = 0.196612f;

  // when
  auto returned = s21::DerivedSigmoid(value);

  // then
  EXPECT_NEAR(exp, returned, ABS_ERROR);
}

TEST(Utils, derived_sigmoid_where_is_equal_to_zero) {

  // given
  auto value = 0.0f;
  auto exp = 0.25f;

  // when
  auto returned = s21::DerivedSigmoid(value);

  // then
  EXPECT_NEAR(exp, returned, ABS_ERROR);
}

TEST(Utils, derived_sigmoid_where_is_equal_to_one) {

  // given
  auto value = 1.0f;
  auto exp = 0.196612f;

  // when
  auto returned = s21::DerivedSigmoid(value);

  // then
  EXPECT_NEAR(exp, returned, ABS_ERROR);
}

TEST(Utils, derived_sigmoid_where_matrix) {

  // given
  auto value = Matrix(1, 3, new float[3]{-1.0f, 0.0f, 1.0f});
  auto exp = Matrix(1, 3, new float[3]{0.196612f, 0.25f,  0.196612f});

  // when
  auto returned = s21::DerivedSigmoid(value);

  // then
  EXPECT_EQ(exp, returned);
}
