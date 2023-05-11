//
// Created by Anton Ivanov on 28.04.2023.
//

#include <gtest/gtest.h>

#include "s21_matrix.h"

TEST(Matrix, multiply_3x3) {

  // given
  auto lhs = Matrix::parse(
      "[[7, 2, 0],"
      " [5, 5, 1],"
      " [2, 3, 4]]");
  auto rhs = Matrix::parse(
      "[[1, 7, 3],"
      " [4, 0, 2],"
      " [7, 3, 3]]");
  auto exp = Matrix::parse(
      "[[ 7, 14, 0],"
      " [20, 0,  2],"
      " [14, 9,  12]]");

  // when
  auto returned = Matrix::multiply(lhs, rhs);

  // then
  EXPECT_EQ(exp, returned);
}

TEST(Matrix, multiply_3x3_where_did_not_change_lhs) {

  // given
  auto lhs = Matrix::parse(
      "[[7, 2, 0],"
      " [5, 5, 1],"
      " [2, 3, 4]]");
  auto rhs = Matrix::parse(
      "[[1, 7, 3],"
      " [4, 0, 2],"
      " [7, 3, 3]]");
  auto exp = Matrix::parse(
      "[[7, 2, 0],"
      " [5, 5, 1],"
      " [2, 3, 4]]");

  // when
  auto returned = Matrix::multiply(lhs, rhs);

  // then
  EXPECT_EQ(exp, lhs);
}

TEST(Matrix, multiply_3x3_where_did_not_change_rhs) {

  // given
  auto lhs = Matrix::parse(
      "[[7, 2, 0],"
      " [5, 5, 1],"
      " [2, 3, 4]]");
  auto rhs = Matrix::parse(
      "[[1, 7, 3],"
      " [4, 0, 2],"
      " [7, 3, 3]]");
  auto exp = Matrix::parse(
      "[[1, 7, 3],"
      " [4, 0, 2],"
      " [7, 3, 3]]");

  // when
  auto returned = Matrix::multiply(lhs, rhs);

  // then
  EXPECT_EQ(exp, rhs);
}

TEST(Matrix, multiply_3x4) {

  // given
  auto lhs = Matrix::parse(
      "[[5, 0, 7, 2],"
      " [1, 8, 6, 8],"
      " [5, 7, 5, 2]]");
  auto rhs = Matrix::parse(
      "[[2, 6, 1, 5],"
      " [0, 1, 2, 0],"
      " [4, 2, 0, 6]]");
  auto exp = Matrix::parse(
      "[[10, 0,  7, 10],"
      " [0,  8, 12,  0],"
      " [20, 14, 0, 12]]");

  // when
  auto returned = Matrix::multiply(lhs, rhs);

  // then
  EXPECT_EQ(exp, returned);
}

TEST(Matrix, multiply_3x4_where_did_not_change_lhs) {

  // given
  auto lhs = Matrix::parse(
      "[[5, 0, 7, 2],"
      " [1, 8, 6, 8],"
      " [5, 7, 5, 2]]");
  auto rhs = Matrix::parse(
      "[[2, 6, 1, 5],"
      " [0, 1, 2, 0],"
      " [4, 2, 0, 6]]");
  auto exp = Matrix::parse(
      "[[5, 0, 7, 2],"
      " [1, 8, 6, 8],"
      " [5, 7, 5, 2]]");

  // when
  auto returned = Matrix::multiply(lhs, rhs);

  // then
  EXPECT_EQ(exp, lhs);
}

TEST(Matrix, multiply_3x4_where_did_not_change_rhs) {

  // given
  auto lhs = Matrix::parse(
      "[[5, 0, 7, 2],"
      " [1, 8, 6, 8],"
      " [5, 7, 5, 2]]");
  auto rhs = Matrix::parse(
      "[[2, 6, 1, 5],"
      " [0, 1, 2, 0],"
      " [4, 2, 0, 6]]");
  auto exp = Matrix::parse(
      "[[2, 6, 1, 5],"
      " [0, 1, 2, 0],"
      " [4, 2, 0, 6]]");

  // when
  auto returned = Matrix::multiply(lhs, rhs);

  // then
  EXPECT_EQ(exp, rhs);
}

TEST(Matrix, multiply_4x3) {

  // given
  auto lhs = Matrix::parse(
      "[[5, 0, 7],"
      " [2, 1, 8],"
      " [6, 8, 5],"
      " [7, 5, 2]]");
  auto rhs = Matrix::parse(
      "[[2, 6, 1],"
      " [5, 0, 1],"
      " [2, 0, 4],"
      " [2, 0, 6]]");
  auto exp = Matrix::parse(
      "[[10, 0,  7],"
      " [10, 0,  8],"
      " [12, 0, 20],"
      " [14, 0, 12]]");

  // when
  auto returned = Matrix::multiply(lhs, rhs);

  // then
  EXPECT_EQ(exp, returned);
}

TEST(Matrix, add_3x3) {

  // given
  auto lhs = Matrix::parse(
      "[[7, 2, 0],"
      " [5, 5, 1],"
      " [2, 3, 4]]");
  auto rhs = Matrix::parse(
      "[[1, 7, 3],"
      " [4, 0, 2],"
      " [7, 3, 3]]");
  auto exp = Matrix::parse(
      "[[8, 9, 3],"
      " [9, 5, 3],"
      " [9, 6, 7]]");

  // when
  auto returned = lhs + rhs;

  // then
  EXPECT_EQ(exp, returned);
}

TEST(Matrix, add_to_3x3) {

  // given
  auto lhs = Matrix::parse(
      "[[7, 2, 0],"
      " [5, 5, 1],"
      " [2, 3, 4]]");
  auto rhs = Matrix::parse(
      "[[1, 7, 3],"
      " [4, 0, 2],"
      " [7, 3, 3]]");
  auto exp = Matrix::parse(
      "[[8, 9, 3],"
      " [9, 5, 3],"
      " [9, 6, 7]]");

  // when
  lhs += rhs;

  // then
  EXPECT_EQ(exp, lhs);
}

TEST(Matrix, add_3x3_where_did_not_change_lhs) {

  // given
  auto lhs = Matrix::parse(
      "[[7, 2, 0],"
      " [5, 5, 1],"
      " [2, 3, 4]]");
  auto rhs = Matrix::parse(
      "[[1, 7, 3],"
      " [4, 0, 2],"
      " [7, 3, 3]]");
  auto exp = Matrix::parse(
      "[[7, 2, 0],"
      " [5, 5, 1],"
      " [2, 3, 4]]");

  // when
  auto returned = lhs + rhs;

  // then
  EXPECT_EQ(exp, lhs);
}

TEST(Matrix, add_3x3_where_did_not_change_rhs) {

  // given
  auto lhs = Matrix::parse(
      "[[7, 2, 0],"
      " [5, 5, 1],"
      " [2, 3, 4]]");
  auto rhs = Matrix::parse(
      "[[1, 7, 3],"
      " [4, 0, 2],"
      " [7, 3, 3]]");
  auto exp = Matrix::parse(
      "[[1, 7, 3],"
      " [4, 0, 2],"
      " [7, 3, 3]]");

  // when
  auto returned = lhs + rhs;

  // then
  EXPECT_EQ(exp, rhs);
}

TEST(Matrix, add_to_3x3_where_did_not_change_rhs) {

  // given
  auto lhs = Matrix::parse(
      "[[7, 2, 0],"
      " [5, 5, 1],"
      " [2, 3, 4]]");
  auto rhs = Matrix::parse(
      "[[1, 7, 3],"
      " [4, 0, 2],"
      " [7, 3, 3]]");
  auto exp = Matrix::parse(
      "[[1, 7, 3],"
      " [4, 0, 2],"
      " [7, 3, 3]]");

  // when
  lhs += rhs;

  // then
  EXPECT_EQ(exp, rhs);
}

TEST(Matrix, add_3x4) {

  // given
  auto lhs = Matrix::parse(
      "[[5, 0, 7, 2],"
      " [1, 8, 6, 8],"
      " [5, 7, 5, 2]]");
  auto rhs = Matrix::parse(
      "[[2, 6, 1, 5],"
      " [0, 1, 2, 0],"
      " [4, 2, 0, 6]]");
  auto exp = Matrix::parse(
      "[[7, 6, 8, 7],"
      " [1, 9, 8, 8],"
      " [9, 9, 5, 8]]");

  // when
  auto returned = lhs + rhs;

  // then
  EXPECT_EQ(exp, returned);
}

TEST(Matrix, add_to_3x4) {

  // given
  auto lhs = Matrix::parse(
      "[[5, 0, 7, 2],"
      " [1, 8, 6, 8],"
      " [5, 7, 5, 2]]");
  auto rhs = Matrix::parse(
      "[[2, 6, 1, 5],"
      " [0, 1, 2, 0],"
      " [4, 2, 0, 6]]");
  auto exp = Matrix::parse(
      "[[7, 6, 8, 7],"
      " [1, 9, 8, 8],"
      " [9, 9, 5, 8]]");

  // when
  lhs += rhs;

  // then
  EXPECT_EQ(exp, lhs);
}

TEST(Matrix, add_3x4_where_did_not_change_lhs) {

  // given
  auto lhs = Matrix::parse(
      "[[5, 0, 7, 2],"
      " [1, 8, 6, 8],"
      " [5, 7, 5, 2]]");
  auto rhs = Matrix::parse(
      "[[2, 6, 1, 5],"
      " [0, 1, 2, 0],"
      " [4, 2, 0, 6]]");
  auto exp = Matrix::parse(
      "[[5, 0, 7, 2],"
      " [1, 8, 6, 8],"
      " [5, 7, 5, 2]]");

  // when
  auto returned = lhs + rhs;

  // then
  EXPECT_EQ(exp, lhs);
}

TEST(Matrix, add_3x4_where_did_not_change_rhs) {

  // given
  auto lhs = Matrix::parse(
      "[[5, 0, 7, 2],"
      " [1, 8, 6, 8],"
      " [5, 7, 5, 2]]");
  auto rhs = Matrix::parse(
      "[[2, 6, 1, 5],"
      " [0, 1, 2, 0],"
      " [4, 2, 0, 6]]");
  auto exp = Matrix::parse(
      "[[2, 6, 1, 5],"
      " [0, 1, 2, 0],"
      " [4, 2, 0, 6]]");

  // when
  auto returned = lhs + rhs;

  // then
  EXPECT_EQ(exp, rhs);
}

TEST(Matrix, add_to_3x4_where_did_not_change_rhs) {

  // given
  auto lhs = Matrix::parse(
      "[[5, 0, 7, 2],"
      " [1, 8, 6, 8],"
      " [5, 7, 5, 2]]");
  auto rhs = Matrix::parse(
      "[[2, 6, 1, 5],"
      " [0, 1, 2, 0],"
      " [4, 2, 0, 6]]");
  auto exp = Matrix::parse(
      "[[2, 6, 1, 5],"
      " [0, 1, 2, 0],"
      " [4, 2, 0, 6]]");

  // when
  lhs += rhs;

  // then
  EXPECT_EQ(exp, rhs);
}

TEST(Matrix, add_4x3) {

  // given
  auto lhs = Matrix::parse(
      "[[5, 0, 7],"
      " [2, 1, 8],"
      " [6, 8, 5],"
      " [7, 5, 2]]");
  auto rhs = Matrix::parse(
      "[[2, 6, 1],"
      " [5, 0, 1],"
      " [2, 0, 4],"
      " [2, 0, 6]]");
  auto exp = Matrix::parse(
      "[[7, 6, 8],"
      " [7, 1, 9],"
      " [8, 8, 9],"
      " [9, 5, 8]]");

  // when
  auto returned = lhs + rhs;

  // then
  EXPECT_EQ(exp, returned);
}

TEST(Matrix, add_to_4x3) {

  // given
  auto lhs = Matrix::parse(
      "[[5, 0, 7],"
      " [2, 1, 8],"
      " [6, 8, 5],"
      " [7, 5, 2]]");
  auto rhs = Matrix::parse(
      "[[2, 6, 1],"
      " [5, 0, 1],"
      " [2, 0, 4],"
      " [2, 0, 6]]");
  auto exp = Matrix::parse(
      "[[7, 6, 8],"
      " [7, 1, 9],"
      " [8, 8, 9],"
      " [9, 5, 8]]");

  // when
  lhs += rhs;

  // then
  EXPECT_EQ(exp, lhs);
}

TEST(Matrix, add_4x3_where_did_not_change_lhs) {

  // given
  auto lhs = Matrix::parse(
      "[[5, 0, 7],"
      " [2, 1, 8],"
      " [6, 8, 5],"
      " [7, 5, 2]]");
  auto rhs = Matrix::parse(
      "[[2, 6, 1],"
      " [5, 0, 1],"
      " [2, 0, 4],"
      " [2, 0, 6]]");
  auto exp = Matrix::parse(
      "[[5, 0, 7],"
      " [2, 1, 8],"
      " [6, 8, 5],"
      " [7, 5, 2]]");

  // when
  auto returned = lhs + rhs;

  // then
  EXPECT_EQ(exp, lhs);
}

TEST(Matrix, add_4x3_where_did_not_change_rhs) {

  // given
  auto lhs = Matrix::parse(
      "[[5, 0, 7],"
      " [2, 1, 8],"
      " [6, 8, 5],"
      " [7, 5, 2]]");
  auto rhs = Matrix::parse(
      "[[2, 6, 1],"
      " [5, 0, 1],"
      " [2, 0, 4],"
      " [2, 0, 6]]");
  auto exp = Matrix::parse(
      "[[2, 6, 1],"
      " [5, 0, 1],"
      " [2, 0, 4],"
      " [2, 0, 6]]");

  // when
  auto returned = lhs + rhs;

  // then
  EXPECT_EQ(exp, rhs);
}

TEST(Matrix, subtraction_3x3) {

  // given
  auto lhs = Matrix::parse(
      "[[7, 2, 0],"
      " [5, 5, 1],"
      " [2, 3, 4]]");
  auto rhs = Matrix::parse(
      "[[1, 7, 3],"
      " [4, 0, 2],"
      " [7, 3, 3]]");
  auto exp = Matrix::parse(
      "[[6, -5, -3],"
      " [1, 5, -1],"
      " [-5, 0, 1]]");

  // when
  auto returned = lhs - rhs;

  // then
  EXPECT_EQ(exp, returned);
}

TEST(Matrix, subtraction_from_3x3) {

  // given
  auto lhs = Matrix::parse(
      "[[7, 2, 0],"
      " [5, 5, 1],"
      " [2, 3, 4]]");
  auto rhs = Matrix::parse(
      "[[1, 7, 3],"
      " [4, 0, 2],"
      " [7, 3, 3]]");
  auto exp = Matrix::parse(
      "[[6, -5, -3],"
      " [1, 5, -1],"
      " [-5, 0, 1]]");

  // when
  lhs -= rhs;

  // then
  EXPECT_EQ(exp, lhs);
}

TEST(Matrix, subtraction_3x3_where_did_not_change_lhs) {

  // given
  auto lhs = Matrix::parse(
      "[[7, 2, 0],"
      " [5, 5, 1],"
      " [2, 3, 4]]");
  auto rhs = Matrix::parse(
      "[[1, 7, 3],"
      " [4, 0, 2],"
      " [7, 3, 3]]");
  auto exp = Matrix::parse(
      "[[7, 2, 0],"
      " [5, 5, 1],"
      " [2, 3, 4]]");

  // when
  auto returned = lhs - rhs;

  // then
  EXPECT_EQ(exp, lhs);
}

TEST(Matrix, subtraction_3x3_where_did_not_change_rhs) {

  // given
  auto lhs = Matrix::parse(
      "[[7, 2, 0],"
      " [5, 5, 1],"
      " [2, 3, 4]]");
  auto rhs = Matrix::parse(
      "[[1, 7, 3],"
      " [4, 0, 2],"
      " [7, 3, 3]]");
  auto exp = Matrix::parse(
      "[[1, 7, 3],"
      " [4, 0, 2],"
      " [7, 3, 3]]");

  // when
  auto returned = lhs - rhs;

  // then
  EXPECT_EQ(exp, rhs);
}

TEST(Matrix, subtraction_3x4) {

  // given
  auto lhs = Matrix::parse(
      "[[5, 0, 7, 2],"
      " [1, 8, 6, 8],"
      " [5, 7, 5, 8]]");
  auto rhs = Matrix::parse(
      "[[2, 6, 1, 5],"
      " [0, 1, 2, 0],"
      " [4, 7, 0, 6]]");
  auto exp = Matrix::parse(
      "[[3, -6, 6, -3],"
      " [1, 7, 4, 8],"
      " [1, 0, 5, 2]]");

  // when
  auto returned = lhs - rhs;

  // then
  EXPECT_EQ(exp, returned);
}

TEST(Matrix, subtraction_from_3x4) {

  // given
  auto lhs = Matrix::parse(
      "[[5, 0, 7, 2],"
      " [1, 8, 6, 8],"
      " [5, 7, 5, 8]]");
  auto rhs = Matrix::parse(
      "[[2, 6, 1, 5],"
      " [0, 1, 2, 0],"
      " [4, 7, 0, 6]]");
  auto exp = Matrix::parse(
      "[[3, -6, 6, -3],"
      " [1, 7, 4, 8],"
      " [1, 0, 5, 2]]");

  // when
  lhs -= rhs;

  // then
  EXPECT_EQ(exp, lhs);
}

TEST(Matrix, subtraction_3x4_where_did_not_change_lhs) {

  // given
  auto lhs = Matrix::parse(
      "[[5, 0, 7, 2],"
      " [1, 8, 6, 8],"
      " [5, 7, 5, 8]]");
  auto rhs = Matrix::parse(
      "[[2, 6, 1, 5],"
      " [0, 1, 2, 0],"
      " [4, 7, 0, 6]]");
  auto exp = Matrix::parse(
      "[[5, 0, 7, 2],"
      " [1, 8, 6, 8],"
      " [5, 7, 5, 8]]");

  // when
  auto returned = lhs - rhs;

  // then
  EXPECT_EQ(exp, lhs);
}

TEST(Matrix, subtraction_3x4_where_did_not_change_rhs) {

  // given
  auto lhs = Matrix::parse(
      "[[5, 0, 7, 2],"
      " [1, 8, 6, 8],"
      " [5, 7, 5, 8]]");
  auto rhs = Matrix::parse(
      "[[2, 6, 1, 5],"
      " [0, 1, 2, 0],"
      " [4, 7, 0, 6]]");
  auto exp = Matrix::parse(
      "[[2, 6, 1, 5],"
      " [0, 1, 2, 0],"
      " [4, 7, 0, 6]]");

  // when
  auto returned = lhs - rhs;

  // then
  EXPECT_EQ(exp, rhs);
}

TEST(Matrix, subtraction_4x3) {

  // given
  auto lhs = Matrix::parse(
      "[[5, 0, 7],"
      " [2, 1, 8],"
      " [6, 8, 5],"
      " [7, 5, 8]]");
  auto rhs = Matrix::parse(
      "[[2, 6, 1],"
      " [5, 0, 1],"
      " [2, 0, 4],"
      " [7, 0, 6]]");
  auto exp = Matrix::parse(
      "[[3, -6, 6],"
      " [-3, 1, 7],"
      " [4, 8, 1],"
      " [0, 5, 2]]");

  // when
  auto returned = lhs - rhs;

  // then
  EXPECT_EQ(exp, returned);
}

TEST(Matrix, subtraction_from_4x3) {

  // given
  auto lhs = Matrix::parse(
      "[[5, 0, 7],"
      " [2, 1, 8],"
      " [6, 8, 5],"
      " [7, 5, 8]]");
  auto rhs = Matrix::parse(
      "[[2, 6, 1],"
      " [5, 0, 1],"
      " [2, 0, 4],"
      " [7, 0, 6]]");
  auto exp = Matrix::parse(
      "[[3, -6, 6],"
      " [-3, 1, 7],"
      " [4, 8, 1],"
      " [0, 5, 2]]");

  // when
  lhs -= rhs;

  // then
  EXPECT_EQ(exp, lhs);
}

TEST(Matrix, subtraction_4x3_where_did_not_change_lhs) {

  // given
  auto lhs = Matrix::parse(
      "[[5, 0, 7],"
      " [2, 1, 8],"
      " [6, 8, 5],"
      " [7, 5, 8]]");
  auto rhs = Matrix::parse(
      "[[2, 6, 1],"
      " [5, 0, 1],"
      " [2, 0, 4],"
      " [7, 0, 6]]");
  auto exp = Matrix::parse(
      "[[5, 0, 7],"
      " [2, 1, 8],"
      " [6, 8, 5],"
      " [7, 5, 8]]");

  // when
  auto returned = lhs - rhs;

  // then
  EXPECT_EQ(exp, lhs);
}

TEST(Matrix, subtraction_4x3_where_did_not_change_rhs) {

  // given
  auto lhs = Matrix::parse(
      "[[5, 0, 7],"
      " [2, 1, 8],"
      " [6, 8, 5],"
      " [7, 5, 8]]");
  auto rhs = Matrix::parse(
      "[[2, 6, 1],"
      " [5, 0, 1],"
      " [2, 0, 4],"
      " [7, 0, 6]]");
  auto exp = Matrix::parse(
      "[[2, 6, 1],"
      " [5, 0, 1],"
      " [2, 0, 4],"
      " [7, 0, 6]]");

  // when
  auto returned = lhs - rhs;

  // then
  EXPECT_EQ(exp, rhs);
}

TEST(Matrix, multiplication_3x3_3x3) {

  // given
  auto lhs = Matrix::parse(
      "[[7, 2, 0],"
      " [5, 5, -1],"
      " [2, 3, -4]]");
  auto rhs = Matrix::parse(
      "[[1, -7, 3],"
      " [4, 0, 2],"
      " [-7, 3, 3]]");
  auto exp = Matrix::parse(
      "[[15, -49, 25],"
      " [32, -38, 22],"
      " [42, -26, 0]]");

  // when
  auto returned = lhs * rhs;

  // then
  EXPECT_EQ(exp, returned);
}

TEST(Matrix, multiplication_3x3_3x3_where_did_not_change_lhs) {

  // given
  auto lhs = Matrix::parse(
      "[[7, 2, 0],"
      " [5, 5, -1],"
      " [2, 3, -4]]");
  auto rhs = Matrix::parse(
      "[[1, -7, 3],"
      " [4, 0, 2],"
      " [-7, 3, 3]]");
  auto exp = Matrix::parse(
      "[[7, 2, 0],"
      " [5, 5, -1],"
      " [2, 3, -4]]");

  // when
  auto returned = lhs * rhs;

  // then
  EXPECT_EQ(exp, lhs);
}

TEST(Matrix, multiplication_3x3_3x3_where_did_not_change_rhs) {

  // given
  auto lhs = Matrix::parse(
      "[[7, 2, 0],"
      " [5, 5, -1],"
      " [2, 3, -4]]");
  auto rhs = Matrix::parse(
      "[[1, -7, 3],"
      " [4, 0, 2],"
      " [-7, 3, 3]]");
  auto exp = Matrix::parse(
      "[[1, -7, 3],"
      " [4, 0, 2],"
      " [-7, 3, 3]]");

  // when
  auto returned = lhs * rhs;

  // then
  EXPECT_EQ(exp, rhs);
}

TEST(Matrix, multiplication_3x4_4x3) {

  // given
  auto lhs = Matrix::parse(
      "[[7, 2, 0, 5],"
      " [5, -1, 2, 3],"
      " [-4, 2, 1, 6]]");
  auto rhs = Matrix::parse(
      "[[1, -7, 3],"
      " [4, 0, 2],"
      " [-7, 3, 3],"
      " [0, 9, 4]]");
  auto exp = Matrix::parse(
      "[[15, -4, 45],"
      " [-13, -2, 31],"
      " [-3, 85, 19]]");

  // when
  auto returned = lhs * rhs;

  // then
  EXPECT_EQ(exp, returned);
}

TEST(Matrix, multiplication_3x4_4x3_where_did_not_change_lhs) {

  // given
  auto lhs = Matrix::parse(
      "[[7, 2, 0, 5],"
      " [5, -1, 2, 3],"
      " [-4, 2, 1, 6]]");
  auto rhs = Matrix::parse(
      "[[1, -7, 3],"
      " [4, 0, 2],"
      " [-7, 3, 3],"
      " [0, 9, 4]]");
  auto exp = Matrix::parse(
      "[[7, 2, 0, 5],"
      " [5, -1, 2, 3],"
      " [-4, 2, 1, 6]]");

  // when
  auto returned = lhs * rhs;

  // then
  EXPECT_EQ(exp, lhs);
}

TEST(Matrix, multiplication_3x4_4x3_where_did_not_change_rhs) {

  // given
  auto lhs = Matrix::parse(
      "[[7, 2, 0, 5],"
      " [5, -1, 2, 3],"
      " [-4, 2, 1, 6]]");
  auto rhs = Matrix::parse(
      "[[1, -7, 3],"
      " [4, 0, 2],"
      " [-7, 3, 3],"
      " [0, 9, 4]]");
  auto exp = Matrix::parse(
      "[[1, -7, 3],"
      " [4, 0, 2],"
      " [-7, 3, 3],"
      " [0, 9, 4]]");

  // when
  auto returned = lhs * rhs;

  // then
  EXPECT_EQ(exp, rhs);
}

TEST(Matrix, multiplication_4x3_3x4) {

  // given
  auto lhs = Matrix::parse(
      "[[7, 2, 0],"
      " [5, 5, -1],"
      " [2, 3, -4],"
      " [2, 1, 6]]");
  auto rhs = Matrix::parse(
      "[[1, -7, 3, 4],"
      " [0, 2, -7, 3],"
      " [3, 0, 9, 4]]");
  auto exp = Matrix::parse(
      "[[7, -45, 7, 34],"
      " [2, -25, -29, 31],"
      " [-10, -8, -51, 1],"
      " [20, -12, 53, 35]]");

  // when
  auto returned = lhs * rhs;

  // then
  EXPECT_EQ(exp, returned);
}

TEST(Matrix, multiplication_4x3_3x4_where_did_not_change_lhs) {

  // given
  auto lhs = Matrix::parse(
      "[[7, 2, 0],"
      " [5, 5, -1],"
      " [2, 3, -4],"
      " [2, 1, 6]]");
  auto rhs = Matrix::parse(
      "[[1, -7, 3, 4],"
      " [0, 2, -7, 3],"
      " [3, 0, 9, 4]]");
  auto exp = Matrix::parse(
      "[[7, 2, 0],"
      " [5, 5, -1],"
      " [2, 3, -4],"
      " [2, 1, 6]]");

  // when
  auto returned = lhs * rhs;

  // then
  EXPECT_EQ(exp, lhs);
}

TEST(Matrix, multiplication_4x3_3x4_where_did_not_change_rhs) {

  // given
  auto lhs = Matrix::parse(
      "[[7, 2, 0],"
      " [5, 5, -1],"
      " [2, 3, -4],"
      " [2, 1, 6]]");
  auto rhs = Matrix::parse(
      "[[1, -7, 3, 4],"
      " [0, 2, -7, 3],"
      " [3, 0, 9, 4]]");
  auto exp = Matrix::parse(
      "[[1, -7, 3, 4],"
      " [0, 2, -7, 3],"
      " [3, 0, 9, 4]]");

  // when
  auto returned = lhs * rhs;

  // then
  EXPECT_EQ(exp, rhs);
}
