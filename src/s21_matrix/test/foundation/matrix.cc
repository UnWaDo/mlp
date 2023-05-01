////
//// Created by Anton Ivanov on 28.04.2023.
////
//
//#include <gtest/gtest.h>
//
//#include "s21_matrix.h"
//
//TEST(Matrix, constructor_m_n_check_m) {
//  auto m = 1;
//  auto n = 2;
//  auto exp = 1;
//
//  auto returned = Matrix(m, n);
//
//  EXPECT_EQ(exp, returned.m);
//}
//
//TEST(Matrix, constructor_m_n_check_n) {
//  auto m = 1;
//  auto n = 2;
//  auto exp = 2;
//
//  auto returned = Matrix(m, n);
//
//  EXPECT_EQ(exp, returned.n);
//}
//
//TEST(Matrix, constructor_m_n_data_check_m) {
//  auto m = 1;
//  auto n = 2;
//  auto data = new float[2]{1, 2};
//  auto exp = 1;
//
//  auto returned = Matrix(m, n, data);
//
//  EXPECT_EQ(exp, returned.m);
//}
//
//TEST(Matrix, constructor_m_n_data_check_n) {
//  auto m = 1;
//  auto n = 2;
//  auto data = new float[2]{1, 2};
//  auto exp = 2;
//
//  auto returned = Matrix(m, n, data);
//
//  EXPECT_EQ(exp, returned.n);
//}
//
//TEST(Matrix, constructor_m_n_data_check_data) {
//  auto m = 1;
//  auto n = 2;
//  auto data = new float[2]{1, 2};
//  auto exp = data;
//
//  auto returned = Matrix(m, n, data);
//
//  EXPECT_EQ(exp, returned.data());
//}
