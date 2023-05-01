//
// Created by Anton Ivanov on 28.04.2023.
//

#include <gtest/gtest.h>

#include "s21_matrix.h"

TEST(Matrix, parse_3x3) {

  // given
  auto data =
      "[[5, 0, 222],"
      " [1, -72, 5],"
      " [-8, 3, 0]]";
  auto exp = Matrix(3,3,new float[9]{5, 0, 222, 1, -72, 5, -8, 3, 0});

  // when
  auto returned = Matrix::parse(data);

  // then
  EXPECT_EQ(exp, returned);
}

TEST(Matrix, parse_3x3_where_with_spaces) {

  // given
  auto data =
      "   [  [5,  0, 222   ] ,     "
      "[  1   ,    -72,    5]   ,  "
      "[ -8,   3,  0  ]   ] ";
  auto exp = Matrix(3,3,new float[9]{5, 0, 222, 1, -72, 5, -8, 3, 0});

  // when
  auto returned = Matrix::parse(data);

  // then
  EXPECT_EQ(exp, returned);
}

TEST(Matrix, parse_3x4) {

  // given
  auto data =
      "[[5, 0, 777, 2],"
      " [1, -84, 6, 8],"
      " [5, 7, 5, 2]]";
  auto exp = Matrix(3,4,new float[12]{5, 0, 777, 2, 1, -84, 6, 8, 5, 7, 5, 2});

  // when
  auto returned = Matrix::parse(data);

  // then
  EXPECT_EQ(exp, returned);
}

TEST(Matrix, parse_3x4_where_with_spaces) {

  // given
  auto data =
      "  [5, 0  ,    777, 2]  ,"
      "  [1  , -84  ,    6, 8] ,  "
      "  [5,  7,   5  ,   2  ]  ]  ";
  auto exp = Matrix(3,4,new float[12]{5, 0, 777, 2, 1, -84, 6, 8, 5, 7, 5, 2});

  // when
  auto returned = Matrix::parse(data);

  // then
  EXPECT_EQ(exp, returned);
}

TEST(Matrix, parse_4x3) {

  // given
  auto data =
      "[[5, 0, 777],"
      " [26, 1, -8],"
      " [6, 8, -59],"
      " [7, 5, 2]]";
  auto exp = Matrix(4, 3, new float[12]{5, 0, 777, 26, 1, -8, 6, 8, -59, 7, 5, 2});

  // when
  auto returned = Matrix::parse(data);

  // then
  EXPECT_EQ(exp, returned);
}

TEST(Matrix, parse_4x3_where_with_spaces) {

  // given
  auto data =
      "[[5  , 0, 777 ] ,  "
      " [26,   1, -8] , "
      " [6,    8, -59    ],"
      " [7,    5,     2  ]  ]";
  auto exp = Matrix(4, 3, new float[12]{5, 0, 777, 26, 1, -8, 6, 8, -59, 7, 5, 2});

  // when
  auto returned = Matrix::parse(data);

  // then
  EXPECT_EQ(exp, returned);
}

TEST(Matrix, parse_throw_empty) {

  // given
  auto data = "";

  // when then
  ASSERT_ANY_THROW(Matrix::parse(data));
}

TEST(Matrix, parse_throw_not_digit) {

  // given
  auto data = "abc";

  // when then
  ASSERT_ANY_THROW(Matrix::parse(data));
}
