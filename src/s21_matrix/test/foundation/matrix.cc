//
// Created by Anton Ivanov on 28.04.2023.
//

#include <gtest/gtest.h>

#include "s21_matrix.h"

TEST(Matrix, constructor_m_n_where_check_m) {

  // given
  auto m = 1;
  auto n = 2;
  auto exp = 1;

  // when
  auto returned = s21::Matrix(m, n);

  // then
  EXPECT_EQ(exp, returned.m());
}

TEST(Matrix, constructor_m_n_where_check_n) {

  // given
  auto m = 1;
  auto n = 2;
  auto exp = 2;

  // when
  auto returned = s21::Matrix(m, n);

  // then
  EXPECT_EQ(exp, returned.n());
}

TEST(Matrix, constructor_m_n_data_where_check_m) {

  // given
  auto m = 1;
  auto n = 2;
  auto data = new float[2]{1, 2};
  auto exp = 1;

  // when
  auto returned = s21::Matrix(m, n, data);

  // then
  EXPECT_EQ(exp, returned.m());
}

TEST(Matrix, constructor_m_n_data_where_check_n) {

  // given
  auto m = 1;
  auto n = 2;
  auto data = new float[2]{1, 2};
  auto exp = 2;

  // when
  auto returned = s21::Matrix(m, n, data);

  // then
  EXPECT_EQ(exp, returned.n());
}

TEST(Matrix, constructor_m_n_data_where_check_data) {

  // given
  auto m = 1;
  auto n = 2;
  auto data = new float[2]{1, 2};
  auto exp = data;

  // when
  auto returned = s21::Matrix(m, n, data);

  // then
  EXPECT_EQ(exp, returned.data());
}

TEST(Matrix, constructor_copy) {

  // given
  auto matrix = s21::Matrix(2, 3, new float[6]{1, 2, 4, 6, 4, 3});
  auto exp = s21::Matrix(2, 3, new float[6]{1, 2, 4, 6, 4, 3});

  // when
  auto returned = s21::Matrix(matrix);

  // then
  EXPECT_EQ(exp, returned);
}

TEST(Matrix, constructor_copy_where_data_for_different_addresses) {

  // given
  auto matrix = s21::Matrix(2, 3, new float[6]{1, 2, 4, 6, 4, 3});
  auto exp = s21::Matrix(2, 3, new float[6]{1, 2, 4, 6, 4, 3});

  // when
  auto returned = s21::Matrix(matrix);

  // then
  EXPECT_TRUE(exp.data() != returned.data());
}
