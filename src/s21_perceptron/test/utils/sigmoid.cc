//
// Created by Anton Ivanov on 29.04.2023.
//

#include <gtest/gtest.h>

#include "s21_utils.h"

TEST(Utils, sigmoid) {

  // given
  auto value = 1.0f;
  auto exp = 0.731059f;

  // when
  auto returned = s21::Sigmoid(value);

  // then
  EXPECT_NEAR(exp, returned, 1e-6f);
}
