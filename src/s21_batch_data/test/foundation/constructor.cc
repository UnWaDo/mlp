#include <gtest/gtest.h>
#include <vector>

#include "s21_batch_data.h"

using namespace s21;

TEST(BatchData, PredictionResultConstructor) {
  // given
  std::size_t classes_number = 10;

  // when
  // then
  ASSERT_NO_THROW(auto pred = PredictionResult(classes_number));
}

TEST(BatchData, PredictionResultAddInvalidResult) {
  // given
  std::size_t classes_number = 10;
  std::size_t expected = 0;
  std::size_t calculated = 11;

  // when
  auto prediction = PredictionResult(classes_number);

  // then
  ASSERT_ANY_THROW(prediction.AddResult(expected, calculated));
}

TEST(BatchData, PredictionResultAddInvalidTarget) {
  // given
  std::size_t classes_number = 10;
  std::size_t expected = 11;
  std::size_t calculated = 0;

  // when
  auto prediction = PredictionResult(classes_number);

  // then
  ASSERT_ANY_THROW(prediction.AddResult(expected, calculated));
}

TEST(BatchData, PredictionResultAddCorrect) {
  // given
  std::size_t classes_number = 10;
  std::size_t expected = 0;
  std::size_t calculated = 0;

  // when
  auto prediction = PredictionResult(classes_number);
  prediction.AddResult(expected, calculated);

  // then
  EXPECT_EQ(prediction.true_positives[expected], 1);
  EXPECT_EQ(prediction.true_negatives[expected], 0);
  EXPECT_EQ(prediction.false_positives[expected], 0);
  EXPECT_EQ(prediction.false_negatives[expected], 0);
  EXPECT_EQ(prediction.true_positives[expected + 1], 0);
  EXPECT_EQ(prediction.true_negatives[expected + 1], 1);
  EXPECT_EQ(prediction.false_positives[expected + 1], 0);
  EXPECT_EQ(prediction.false_negatives[expected + 1], 0);
}

TEST(BatchData, PredictionResultAddIncorrect) {
  // given
  std::size_t classes_number = 10;
  std::size_t expected = 0;
  std::size_t calculated = 1;

  // when
  auto prediction = PredictionResult(classes_number);
  prediction.AddResult(expected, calculated);

  // then
  EXPECT_EQ(prediction.true_positives[expected], 0);
  EXPECT_EQ(prediction.true_negatives[expected], 0);
  EXPECT_EQ(prediction.false_positives[expected], 0);
  EXPECT_EQ(prediction.false_negatives[expected], 1);
  EXPECT_EQ(prediction.true_positives[expected + 1], 0);
  EXPECT_EQ(prediction.true_negatives[expected + 1], 0);
  EXPECT_EQ(prediction.false_positives[expected + 1], 1);
  EXPECT_EQ(prediction.false_negatives[expected + 1], 0);
}

TEST(BatchData, PredictionResultAddSome) {
  // given
  std::size_t classes_number = 10;
  std::size_t expected = 0;

  // when
  auto prediction = PredictionResult(classes_number);
  for (std::size_t i = 0; i < 10; i++)
    prediction.AddResult(expected, i % 2);

  // then
  EXPECT_EQ(prediction.true_positives[expected], 5);
  EXPECT_EQ(prediction.true_negatives[expected], 0);
  EXPECT_EQ(prediction.false_positives[expected], 0);
  EXPECT_EQ(prediction.false_negatives[expected], 5);
  EXPECT_EQ(prediction.true_positives[expected + 1], 0);
  EXPECT_EQ(prediction.true_negatives[expected + 1], 5);
  EXPECT_EQ(prediction.false_positives[expected + 1], 5);
  EXPECT_EQ(prediction.false_negatives[expected + 1], 0);
}

TEST(BatchData, PredictionResultAddInvalidMatrix) {
  // given
  std::size_t classes_number = 10;
  std::size_t expected = 0;
  auto result = Matrix(1, int(classes_number * 2));

  // when
  auto prediction = PredictionResult(classes_number);

  // then
  ASSERT_ANY_THROW(prediction.AddResult(expected, result));
}
TEST(BatchData, PredictionResultAddMatrix) {
  // given
  std::size_t classes_number = 10;
  std::size_t expected = 0;
  auto result = Matrix(1, int(classes_number));

  // when
  result[0][0] = 1;
  for (std::size_t i = 1; i < classes_number; i++) {
    result[0][i] = 0;
  }
  auto prediction = PredictionResult(classes_number);
  prediction.AddResult(expected, result);

  // then
  EXPECT_EQ(prediction.true_positives[expected], 1);
  EXPECT_EQ(prediction.true_negatives[expected], 0);
  EXPECT_EQ(prediction.false_positives[expected], 0);
  EXPECT_EQ(prediction.false_negatives[expected], 0);
  EXPECT_EQ(prediction.true_positives[expected + 1], 0);
  EXPECT_EQ(prediction.true_negatives[expected + 1], 1);
  EXPECT_EQ(prediction.false_positives[expected + 1], 0);
  EXPECT_EQ(prediction.false_negatives[expected + 1], 0);
}

TEST(BatchData, MetricValuesDefault) {
  // given
  // when
  auto metric = MetricValues();

  // then
  EXPECT_EQ(metric.accuracy, 0);
  EXPECT_EQ(metric.precision, 0);
  EXPECT_EQ(metric.recall, 0);
  EXPECT_EQ(metric.f_measure, 0);
}

TEST(BatchData, MetricValuesAllFit) {
  // given
  std::size_t classes_number = 10;

  // when
  auto prediction = PredictionResult(classes_number);
  for (std::size_t i = 0; i < 10; i++)
    prediction.AddResult(i, i);
  auto metric = MetricValues(prediction);

  // then
  EXPECT_NEAR(metric.accuracy, 1, 1e-4);
  EXPECT_NEAR(metric.precision, 1, 1e-4);
  EXPECT_NEAR(metric.recall, 1, 1e-4);
  EXPECT_NEAR(metric.f_measure, 1, 1e-4);
}

TEST(BatchData, MetricValuesWithErrors) {
  // given
  std::size_t classes_number = 3;
  auto expected_acc = (0.6 + 0.7 + 0.7) / 3;
  auto expected_prec = (0.4 + 0.5 + 1) / 3;
  auto expected_rec = (4.0 / 3.0 + 0.25) / 3.0;
  auto expected_f = 2.0 / (1 / expected_prec + 1 / expected_rec);

  // when
  auto prediction = PredictionResult(classes_number);
  for (std::size_t i = 0; i < 9; i++)
    prediction.AddResult(i % 3, i % 2);
  prediction.AddResult(2, 2);
  auto metric = MetricValues(prediction);

  // then
  EXPECT_NEAR(metric.accuracy, expected_acc, 1e-4);
  EXPECT_NEAR(metric.precision, expected_prec, 1e-4);
  EXPECT_NEAR(metric.recall, expected_rec, 1e-4);
  EXPECT_NEAR(metric.f_measure, expected_f, 1e-4);
}

TEST(BatchData, MetricValuesAllErrors) {
  // given
  std::size_t classes_number = 10;

  // when
  auto prediction = PredictionResult(classes_number);
  for (std::size_t i = 0; i < 10; i++)
    prediction.AddResult(i, (i + 1) % classes_number);
  auto metric = MetricValues(prediction);

  // then
  EXPECT_NEAR(metric.accuracy, 0.8, 1e-4);
  EXPECT_NEAR(metric.precision, 0, 1e-4);
  EXPECT_NEAR(metric.recall, 0, 1e-4);
}

TEST(BatchData, TestConstructor) {
  // given
  std::size_t class_number = 26;
  std::size_t input_length = 28 * 28;

  // when
  BatchData data = BatchData(class_number, input_length);

  // then
  ASSERT_EQ(data.GetClassesNumber(), class_number);
  ASSERT_EQ(data.GetInputLength(), input_length);
  ASSERT_EQ(data.GetMaxSteps(), DEFAULT_MAX_STEPS);
}

TEST(BatchData, CreateDataSample) {
  // given
  Matrix m = Matrix(1, 28 * 28);
  std::size_t classes_number = 26;
  std::size_t class_value = 1;

  // when
  auto sample = DataSample(m, class_value);
  auto repr = sample.GetTargetRepresentation(classes_number);

  // then
  ASSERT_EQ(sample.input, m);
  ASSERT_EQ(sample.target, class_value);
  ASSERT_EQ(repr.m(), 1);
  ASSERT_EQ(std::size_t(repr.n()), classes_number);
}
