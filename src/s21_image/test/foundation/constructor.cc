#include <gtest/gtest.h>
#include <vector>

#include "s21_image.h"

using namespace s21;

TEST(ImageLoadTest, NullptrInit) {
  // given
  // when
  // then
  ASSERT_ANY_THROW(auto img = Image(nullptr));
}

TEST(ImageLoadTest, NonexistingInit) {
  // given
  std::string filename("never_existed.file");

  // when
  // then
  ASSERT_ANY_THROW(auto img = Image(filename));
}

TEST(ImageLoadTest, NonBMPInit) {
  // given
  std::string filename("resource/grayscale.png");

  // when
  // then
  ASSERT_ANY_THROW(auto img = Image(filename));
}

TEST(ImageLoadTest, BadBMPInit) {
  // given
  std::string filename("resource/bad.bmp");

  // when
  // then
  ASSERT_ANY_THROW(auto img = Image(filename));
}

TEST(ImageLoadTest, LoadBMP) {
  // given
  std::string filename("resource/grayscale.bmp");

  // when
  // then
  ASSERT_NO_THROW(auto img = Image(filename));
}
