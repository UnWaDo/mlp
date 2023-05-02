#include <gtest/gtest.h>
#include "s21_batch_data_test.h"
#include "s21_perceptron.h"
#include "s21_matrix_perceptron.h"

using namespace s21;

TEST_F(BatchDataTest, TestValidationOnWhole) {
  // given
  std::string filename("resource/data.csv");

  // when
  data.LoadData(filename);
  auto results = data.Validate(perceptron);

  // then
  EXPECT_NEAR(results.accuracy, 0.9720, 1e-4);
  EXPECT_NEAR(results.precision, 0.9517, 1e-4);
  EXPECT_NEAR(results.recall, 0.9263, 1e-4);
  EXPECT_NEAR(results.f_measure, 0.9388, 1e-4);
}

TEST_F(BatchDataTest, TestValidationOnFirstHalf) {
  // given
  std::string filename("resource/data.csv");

  // when
  data.LoadData(filename);
  auto results = data.Validate(perceptron, 0, data.GetDataSize() / 2);

  // then
  EXPECT_NEAR(results.accuracy, 0.9680, 1e-4);
  EXPECT_NEAR(results.precision, 0.9467, 1e-4);
  EXPECT_NEAR(results.recall, 0.9111, 1e-4);
  EXPECT_NEAR(results.f_measure, 0.9285, 1e-4);
}

TEST_F(BatchDataTest, TestValidationOnSecondHalf) {
  // given
  std::string filename("resource/data.csv");

  // when
  data.LoadData(filename);
  auto results = data.Validate(perceptron, data.GetDataSize() / 2, data.GetDataSize());

  // then
  EXPECT_NEAR(results.accuracy, 0.9760, 1e-4);
  EXPECT_NEAR(results.precision, 0.9571, 1e-4);
  EXPECT_NEAR(results.recall, 0.9400, 1e-4);
  EXPECT_NEAR(results.f_measure, 0.9485, 1e-4);
}

TEST_F(BatchDataTest, TestCrossValidation) {
  // given
  std::string filename("resource/data.csv");

  // when
  data.LoadData(filename);
  auto results = data.KCrossValidation(perceptron, 3);

  // then
  EXPECT_GT(results.accuracy, 0.9);
  EXPECT_GT(results.precision, 0.9);
  EXPECT_GT(results.recall, 0.9);
  EXPECT_GT(results.f_measure, 0.9);
}
