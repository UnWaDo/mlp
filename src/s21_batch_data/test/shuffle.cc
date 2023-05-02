#include <gtest/gtest.h>
#include "s21_batch_data_test.h"
#include "s21_perceptron.h"
#include "s21_matrix_perceptron.h"

#include <iostream>

using namespace s21;

TEST_F(BatchDataTest, TestRandomShuffle) {
  // given
  std::string filename("resource/data.csv");

  // when
  data.LoadData(filename);
  std::vector<DataSample> samples;
  samples.reserve(data.GetDataSize());
  for (std::size_t i = 0; i < data.GetDataSize(); i++) {
    samples.push_back(data.GetSample(i));
  }
  data.ShuffleData();

  // then
  ASSERT_EQ(data.GetDataSize(), samples.size());
  std::size_t matching = 0;
  for (std::size_t i = 0; i < data.GetDataSize(); i++) {
    auto sample = data.GetSample(i);
    bool found = false;
    for (std::size_t j = 0; j < samples.size(); j++) {
      if (sample.input == samples[j].input && sample.target == samples[j].target) {
        matching += (i == j);
        found = true;
        break ;
      }
    }
    if (!found)
      std::cout << i << std::endl << sample.input << std::endl << sample.target << std::endl;
    ASSERT_TRUE(found);
  }
  ASSERT_NE(matching, data.GetDataSize());
}
