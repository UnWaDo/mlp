#include <gtest/gtest.h>
#include <vector>

#include "s21_batch_data.h"
#include "s21_batch_data_test.h"

using namespace s21;

TEST_F(BatchDataTest, TestGetClassesNumber) {
  // given
  // when
  // then
  ASSERT_EQ(data.GetClassesNumber(), 5);
}

TEST_F(BatchDataTest, TestGetInputLength) {
  // given
  // when
  // then
  ASSERT_EQ(data.GetInputLength(), 30);
}

TEST_F(BatchDataTest, TestGetMaxSteps) {
  // given
  // when
  // then
  ASSERT_EQ(data.GetMaxSteps(), DEFAULT_MAX_STEPS);
}

TEST_F(BatchDataTest, TestGetEmptySize) {
  // given
  // when
  // then
  ASSERT_EQ(data.GetDataSize(), 0);
}

TEST_F(BatchDataTest, TestGetNormalSize) {
  // given
  // when
  data.LoadData("resource/data.csv");

  // then
  ASSERT_EQ(data.GetDataSize(), 100);
}

TEST_F(BatchDataTest, TestGetFirstSample) {
  // given
  int target = 1;
  int inputs[] = {
     10,  11,  10,   9,   8,  11,
     11,   8,  12,   9,   6,   7,
      8,  12,   6,   9,  12,  12,
      8,  10,  11,   7,  11,  10,
     10,   7,  11,   6,   8,  11
  };
  std::size_t data_len = sizeof(inputs) / sizeof(*inputs);

  // when
  float *inputs_alloc = new float[data_len];
  for (std::size_t i = 0; i < data_len; i++)
    inputs_alloc[i] = 1.0 * inputs[i] / 255;
  Matrix input_value = Matrix(1, data_len, inputs_alloc);
  data.LoadData("resource/data.csv");

  // then
  auto sample = data.GetSample(0);
  ASSERT_EQ(sample.input, input_value);
  ASSERT_EQ(sample.target, target);
}

TEST_F(BatchDataTest, TestGetRandomSample) {
  // given
  data.LoadData("resource/data.csv");
  std::size_t number = 10;

  // when
  std::vector<DataSample> samples;
  for (std::size_t i = 0; i < number; i++)
    samples.emplace_back(data.GetRandomSample());

  // then
  std::size_t equal = 0;
  for (std::size_t i = 0; i < samples.size(); i++)
    equal += (samples[i].input == samples[0].input) && (samples[i].target == samples[0].target);
  ASSERT_LE(equal, 3);
}

TEST_F(BatchDataTest, TestGetFirstSampleRepresentation) {
  // given
  int classes[] = {0,   1,   0,   0,   0};
  int inputs[] = {
     10,  11,  10,   9,   8,  11,
     11,   8,  12,   9,   6,   7,
      8,  12,   6,   9,  12,  12,
      8,  10,  11,   7,  11,  10,
     10,   7,  11,   6,   8,  11
  };
  std::size_t inputs_len = data.GetInputLength();
  std::size_t output_len = data.GetClassesNumber();

  // when
  float *inputs_alloc = new float[inputs_len];
  for (std::size_t i = 0; i < inputs_len; i++)
    inputs_alloc[i] = 1.0 * inputs[i] / 255;
  float *outputs_alloc = new float[output_len];
  for (std::size_t i = 0; i < output_len; i++)
    outputs_alloc[i] = classes[i];
  Matrix input_value = Matrix(1, inputs_len, inputs_alloc);
  Matrix output_value = Matrix(1, output_len, outputs_alloc);
  data.LoadData("resource/data.csv");

  // then
  auto sample = data.GetSample(0);
  ASSERT_EQ(sample.input, input_value);
  ASSERT_EQ(sample.GetTargetRepresentation(output_len), output_value);
}
