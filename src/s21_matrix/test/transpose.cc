//
// Created by Anton Ivanov on 28.04.2023.
//

#include <gtest/gtest.h>

#include "s21_matrix.h"

TEST(Matrix, transpose_3x3) {

  // given
  auto sut = Matrix::parse(
      "[[5, 0, 2],"
      " [1, 7, 5],"
      " [8, 3, 0]]");
  auto exp = Matrix::parse(
      "[[5, 1, 8],"
      " [0, 7, 3],"
      " [2, 5, 0]]");

  // when
  auto returned = sut.transpose();

  // then
  EXPECT_EQ(exp, returned);
}

TEST(Matrix, transpose_3x3_where_did_not_change) {

  // given
  auto sut = Matrix::parse(
      "[[5, 0, 2],"
      " [1, 7, 5],"
      " [8, 3, 0]]");
  auto exp = Matrix::parse(
      "[[5, 0, 2],"
      " [1, 7, 5],"
      " [8, 3, 0]]");

  // when
  auto returned = sut.transpose();

  // then
  EXPECT_EQ(exp, sut);
}

TEST(Matrix, transpose_3x4) {

  // given
  auto sut = Matrix::parse(
      "[[5, 0, 7, 2],"
      " [1, 8, 6, 8],"
      " [5, 7, 5, 2]]");
  auto exp = Matrix::parse(
      "[[5, 1, 5],"
      " [0, 8, 7],"
      " [7, 6, 5],"
      " [2, 8, 2]]");

  // when
  auto returned = sut.transpose();

  // then
  EXPECT_EQ(exp, returned);
}

TEST(Matrix, transpose_3x4_where_did_not_change) {

  // given
  auto sut = Matrix::parse(
      "[[5, 0, 7, 2],"
      " [1, 8, 6, 8],"
      " [5, 7, 5, 2]]");
  auto exp = Matrix::parse(
      "[[5, 0, 7, 2],"
      " [1, 8, 6, 8],"
      " [5, 7, 5, 2]]");

  // when
  auto returned = sut.transpose();

  // then
  EXPECT_EQ(exp, sut);
}

TEST(Matrix, transpose_4x3) {

  // given
  auto sut = Matrix::parse(
      "[[5, 0, 7],"
      " [2, 1, 8],"
      " [6, 8, 5],"
      " [7, 5, 2]]");
  auto exp = Matrix::parse(
      "[[5, 2, 6, 7],"
      " [0, 1, 8, 5],"
      " [7, 8, 5, 2]]");

  // when
  auto returned = sut.transpose();

  // then
  EXPECT_EQ(exp, returned);
}

TEST(Matrix, transpose_4x3_where_did_not_change) {

  // given
  auto sut = Matrix::parse(
      "[[5, 0, 7],"
      " [2, 1, 8],"
      " [6, 8, 5],"
      " [7, 5, 2]]");
  auto exp = Matrix::parse(
      "[[5, 0, 7],"
      " [2, 1, 8],"
      " [6, 8, 5],"
      " [7, 5, 2]]");

  // when
  auto returned = sut.transpose();

  // then
  EXPECT_EQ(exp, sut);
}
