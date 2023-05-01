#include <gtest/gtest.h>

#include "s21_image.h"
#include "s21_image_test.h"

TEST_F(ImageTest, TestSaveToDir) {
  // given
  auto path = testing::TempDir();

  // when
  // then
  ASSERT_ANY_THROW(grayscale.ToFile(path));
}

TEST_F(ImageTest, TestSaveToFile) {
  // given
  auto path = testing::TempDir() + "output.bmp";

  // when
  // then
  ASSERT_NO_THROW(grayscale.ToFile(path));
}

TEST_F(ImageTest, TestSaveToFileAndCheckGrayscale) {
  // given
  auto path = testing::TempDir() + "output.bmp";

  // when
  grayscale.ToFile(path);
  auto written = s21::Image(path);

  // then
  ASSERT_EQ(grayscale.GetWidth(), written.GetWidth());
  ASSERT_EQ(grayscale.GetHeight(), written.GetHeight());
  ASSERT_EQ(grayscale.GetBitsPerPixel(), written.GetBitsPerPixel());
  for (std::size_t x = 0; x < grayscale.GetWidth(); x++) {
    for (std::size_t y = 0; y < grayscale.GetHeight(); y++) {
      ASSERT_EQ(grayscale.GetPixel(x, y), written.GetPixel(x, y));
    }
  }
}

TEST_F(ImageTest, TestSaveToFileAndCheckRGB) {
  // given
  auto path = testing::TempDir() + "output.bmp";

  // when
  rgb.ToFile(path);
  auto written = s21::Image(path);

  // then
  ASSERT_EQ(rgb.GetWidth(), written.GetWidth());
  ASSERT_EQ(rgb.GetHeight(), written.GetHeight());
  ASSERT_EQ(rgb.GetBitsPerPixel(), written.GetBitsPerPixel());
  for (std::size_t x = 0; x < rgb.GetWidth(); x++) {
    for (std::size_t y = 0; y < rgb.GetHeight(); y++) {
      ASSERT_EQ(rgb.GetPixel(x, y), written.GetPixel(x, y));
    }
  }
}