//
// Created by Anton Ivanov on 30.04.2023.
//

#include <gtest/gtest.h>

#include <filesystem>

#include "s21_matrix_perceptron.h"

TEST(MatrixPerceptron, ExportPerceptronToFile_where_3_2_2_1) {

  // given
  std::filesystem::remove_all("test_export");
  auto sut = MatrixPerceptron("perceptron_3_2_2_1", "resource/");

  // when then
  EXPECT_NO_THROW(sut.ExportPerceptronToFile("perceptron_3_2_2_1", "test_export/"));
}

TEST(MatrixPerceptron, ExportPerceptronToFile_where_3_32_128_4) {

  // given
  std::filesystem::remove_all("test_export");
  auto sut = MatrixPerceptron("perceptron_3_32_128_4", "resource/");

  // when then
  EXPECT_NO_THROW(sut.ExportPerceptronToFile("perceptron_3_32_128_4", "test_export/"));
}

TEST(MatrixPerceptron, ExportPerceptronToFile_where_4_64_30_12_10) {

  // given
  std::filesystem::remove_all("test_export");
  auto sut = MatrixPerceptron("perceptron_4_64_30_12_10", "resource/");

  // when then
  EXPECT_NO_THROW(sut.ExportPerceptronToFile("perceptron_4_64_30_12_10", "test_export/"));
}

