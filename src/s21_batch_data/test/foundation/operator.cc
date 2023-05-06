#include <gtest/gtest.h>

#include "s21_batch_data.h"

using namespace s21;

TEST(MetricValues, TestAddition) {
  // given
  auto metric_1 = MetricValues();
  auto metric_2 = MetricValues();
  auto m1_values = 0.5;
  auto m2_values = 0.1;

  // when
  metric_1.accuracy = m1_values;
  metric_1.precision = m1_values;
  metric_1.recall = m1_values;
  metric_1.f_measure = m1_values;
  metric_2.accuracy = m2_values;
  metric_2.precision = m2_values;
  metric_2.recall = m2_values;
  metric_2.f_measure = m2_values;
  metric_1 += metric_2;

  // then
  ASSERT_NEAR(metric_1.accuracy, m1_values + m2_values, 1e-6);
  ASSERT_NEAR(metric_1.precision, m1_values + m2_values, 1e-6);
  ASSERT_NEAR(metric_1.recall, m1_values + m2_values, 1e-6);
  ASSERT_NEAR(metric_1.f_measure, m1_values + m2_values, 1e-6);
  ASSERT_NEAR(metric_2.accuracy, m2_values, 1e-6);
  ASSERT_NEAR(metric_2.precision, m2_values, 1e-6);
  ASSERT_NEAR(metric_2.recall, m2_values, 1e-6);
  ASSERT_NEAR(metric_2.f_measure, m2_values, 1e-6);
}

TEST(MetricValues, TestDivision) {
  // given
  auto metric = MetricValues();
  auto values = 0.5;
  std::size_t div = 5;

  // when
  metric.accuracy = values;
  metric.precision = values;
  metric.recall = values;
  metric.f_measure = values;
  metric /= div;

  // then
  ASSERT_NEAR(metric.accuracy, values / div, 1e-6);
  ASSERT_NEAR(metric.precision, values / div, 1e-6);
  ASSERT_NEAR(metric.recall, values / div, 1e-6);
  ASSERT_NEAR(metric.f_measure, values / div, 1e-6);
}
