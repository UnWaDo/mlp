#include <gtest/gtest.h>
#include "s21_batch_data_test.h"

TEST_F(BatchDataTest, NonexistingInit) {
  // given
  std::string filename("never_existed.file");

  // when
  // then
  ASSERT_ANY_THROW(data.LoadData(filename));
}

TEST_F(BatchDataTest, TooLargeInputLengthInit) {
  // given
  std::string filename("resource/5_45.csv");

  // when
  // then
  ASSERT_ANY_THROW(data.LoadData(filename));
}

TEST_F(BatchDataTest, TooSmallInputLengthInit) {
  // given
  std::string filename("resource/5_15.csv");

  // when
  // then
  ASSERT_ANY_THROW(data.LoadData(filename));
}

TEST_F(BatchDataTest, TooLargeClassNumberInit) {
  // given
  std::string filename("resource/10_30.csv");

  // when
  // then
  ASSERT_ANY_THROW(data.LoadData(filename));
}

TEST_F(BatchDataTest, LoadNormalFile) {
  // given
  std::string filename("resource/5_30.csv");

  // when
  // then
  ASSERT_NO_THROW(data.LoadData(filename));
  ASSERT_EQ(data.GetDataSize(), 10);
}

TEST_F(BatchDataTest, LoadFileWithData) {
  // given
  std::string filename("resource/data.csv");

  // when
  // then
  ASSERT_NO_THROW(data.LoadData(filename));
  ASSERT_EQ(data.GetDataSize(), 100);
}

TEST_F(BatchDataTest, PurgeData) {
  // given
  std::string filename("resource/5_30.csv");

  // when
  data.LoadData(filename);
  data.PurgeData();

  // then
  ASSERT_EQ(data.GetDataSize(), 0);
}
