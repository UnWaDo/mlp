//
// Created by Anton Ivanov on 28.04.2023.
//

#include <gtest/gtest.h>

#include "s21_matrix.h"

TEST(Matrix, description_3x3) {

  // given
  auto sut = Matrix::parse(
      "[[5, 0, 222],"
      " [1, -72, 5],"
      " [-8, 3, 0]]");
  auto exp(
      "[[5.000000, 0.000000, 222.000000],"
      " [1.000000, -72.000000, 5.000000],"
      " [-8.000000, 3.000000, 0.000000]]");

  // when
  auto returned = sut.description();

  // then
  EXPECT_EQ(exp, returned);
}

TEST(Matrix, description_3x3_with_separator) {

  // given
  auto separator("_SEPARATOR_");
  auto sut = Matrix::parse(
      "[[5, 0, 222],"
      " [1, -72, 5],"
      " [-8, 3, 0]]");
  auto exp(
      "[[5.000000, 0.000000, 222.000000],_SEPARATOR_"
      "[1.000000, -72.000000, 5.000000],_SEPARATOR_"
      "[-8.000000, 3.000000, 0.000000]]");

  // when
  auto returned = sut.description(separator);

  // then
  EXPECT_EQ(exp, returned);
}

TEST(Matrix, description_3x4) {

  // given
  auto sut = Matrix::parse(
      "[[5, 0, 777, 2],"
      " [1, -84, 6, 8],"
      " [5, 7, 5, 2]]");
  auto exp(
      "[[5.000000, 0.000000, 777.000000, 2.000000],"
      " [1.000000, -84.000000, 6.000000, 8.000000],"
      " [5.000000, 7.000000, 5.000000, 2.000000]]");

  // when
  auto returned = sut.description();

  // then
  EXPECT_EQ(exp, returned);
}

TEST(Matrix, description_3x4_with_separator) {

  // given
  auto separator("_SEPARATOR_");
  auto sut = Matrix::parse(
      "[[5, 0, 777, 2],"
      " [1, -84, 6, 8],"
      " [5, 7, 5, 2]]");
  auto exp(
      "[[5.000000, 0.000000, 777.000000, 2.000000],_SEPARATOR_"
      "[1.000000, -84.000000, 6.000000, 8.000000],_SEPARATOR_"
      "[5.000000, 7.000000, 5.000000, 2.000000]]");

  // when
  auto returned = sut.description(separator);

  // then
  EXPECT_EQ(exp, returned);
}

TEST(Matrix, description_4x3) {

  // given
  auto sut = Matrix::parse(
      "[[5, 0, 777],"
      " [26, 1, -8],"
      " [6, 8, -59],"
      " [7, 5, 2]]");
  auto exp(
      "[[5.000000, 0.000000, 777.000000],"
      " [26.000000, 1.000000, -8.000000],"
      " [6.000000, 8.000000, -59.000000],"
      " [7.000000, 5.000000, 2.000000]]");

  // when
  auto returned = sut.description();

  // then
  EXPECT_EQ(exp, returned);
}

TEST(Matrix, description_4x3_with_separator) {

  // given
  auto separator("_SEPARATOR_");
  auto sut = Matrix::parse(
      "[[5, 0, 777],"
      " [26, 1, -8],"
      " [6, 8, -59],"
      " [7, 5, 2]]");
  auto exp(
      "[[5.000000, 0.000000, 777.000000],_SEPARATOR_"
      "[26.000000, 1.000000, -8.000000],_SEPARATOR_"
      "[6.000000, 8.000000, -59.000000],_SEPARATOR_"
      "[7.000000, 5.000000, 2.000000]]");

  // when
  auto returned = sut.description(separator);

  // then
  EXPECT_EQ(exp, returned);
}
