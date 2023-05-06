//
// Created by Anton Ivanov on 28.04.2023.
//

#include <gtest/gtest.h>

#include "s21_matrix.h"


TEST(Matrix, is_equal) {
  auto lhs = Matrix::parse(
      "[[1, 2],"
      " [3, 4]]");
  auto rhs = Matrix::parse(
      "[[1, 2],"
      " [3, 4]]");

  auto returned = lhs == rhs;

  EXPECT_TRUE(returned);
}

TEST(Matrix, is_equal_floats) {
  auto lhs = Matrix::parse(
      "[[1.1, 2.01],"
      " [3.001, 4.0001]]");
  auto rhs = Matrix::parse(
      "[[1.1, 2.01],"
      " [3.001, 4.0001]]");

  auto returned = lhs == rhs;

  EXPECT_TRUE(returned);
}

TEST(Matrix, is_not_equal_because_of_m) {
  auto lhs = Matrix::parse(
      "[[1, 2],"
      " [2, 3]]");
  auto rhs = Matrix::parse("[[1, 2]]");

  auto returned = lhs == rhs;

  EXPECT_FALSE(returned);
}

TEST(Matrix, is_not_equal_because_of_n) {
  auto lhs = Matrix::parse(
      "[[1, 2],"
      " [2, 3]]");
  auto rhs = Matrix::parse(
      "[[1],"
      " [2]]");

  auto returned = lhs == rhs;

  EXPECT_FALSE(returned);
}

TEST(Matrix, is_not_equal_because_of_m_and_n) {
  auto lhs = Matrix::parse(
      "[[1, 2],"
      " [2, 3]]");
  auto rhs = Matrix::parse("[[1]]");

  auto returned = lhs == rhs;

  EXPECT_FALSE(returned);
}

TEST(Matrix, is_not_equal_because_of_value) {
  auto lhs = Matrix::parse(
      "[[1, 2],"
      " [2, 3]]");
  auto rhs = Matrix::parse(
      "[[1, 2],"
      " [9, 3]]");

  auto returned = lhs == rhs;

  EXPECT_FALSE(returned);
}

TEST(Matrix, is_not_equal_because_of_value_floats) {
  auto lhs = Matrix::parse(
      "[[1.1, 2.1],"
      " [2.0, 3.1]]");
  auto rhs = Matrix::parse(
      "[[1.01, 2.1],"
      " [2.0, 3.1]]");

  auto returned = lhs == rhs;

  EXPECT_FALSE(returned);
}

TEST(Matrix, outstream_3x3_default) {
  std::stringstream stream;
  auto sut = Matrix::parse(
      "[[5, 0, 222],"
      " [1, -72, 5],"
      " [-8, 3, 0]]");
  auto exp(
      "[[5.000000, 0.000000, 222.000000],"
      " [1.000000, -72.000000, 5.000000],"
      " [-8.000000, 3.000000, 0.000000]]");

  stream << sut;

  EXPECT_EQ(exp, stream.str());
}

TEST(Matrix, outstream_3x4_default) {
  std::stringstream stream;
  auto sut = Matrix::parse(
      "[[5, 0, 777, 2],"
      " [1, -84, 6, 8],"
      " [5, 7, 5, 2]]");
  auto exp(
      "[[5.000000, 0.000000, 777.000000, 2.000000],"
      " [1.000000, -84.000000, 6.000000, 8.000000],"
      " [5.000000, 7.000000, 5.000000, 2.000000]]");

  stream << sut;

  EXPECT_EQ(exp, stream.str());
}

TEST(Matrix, outstream_4x3_default) {
  std::stringstream stream;
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

  stream << sut;

  EXPECT_EQ(exp, stream.str());
}
