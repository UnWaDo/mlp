#include <gtest/gtest.h>
#include "s21_batch_data_test.h"
#include "s21_perceptron.h"
#include "s21_matrix_perceptron.h"

using namespace s21;

#include <iostream>

TEST_F(BatchDataTest, TestTrainOnWholeDataset) {
  // given
  std::string filename("resource/data.csv");

  // when
  data.LoadData(filename);
  auto before = data.Validate(perceptron);
  data.Train(perceptron);
  auto after = data.Validate(perceptron);

  // then
  EXPECT_GT(after.accuracy, before.accuracy);
  EXPECT_GT(after.precision, before.precision);
  EXPECT_GT(after.recall, before.recall);
  EXPECT_GT(after.f_measure, before.f_measure);
}

TEST_F(BatchDataTest, TestTrainWithCallBack) {
  // given
  std::string filename("resource/data.csv");

  // when
  data.LoadData(filename);
  auto before = data.Validate(perceptron);
  data.Train(perceptron, [](std::size_t e, MetricValues m) -> void {
    (void) e;
    (void) m;
  });
  auto after = data.Validate(perceptron);

  // then
  EXPECT_GT(after.accuracy, before.accuracy);
  EXPECT_GT(after.precision, before.precision);
  EXPECT_GT(after.recall, before.recall);
  EXPECT_GT(after.f_measure, before.f_measure);
}
