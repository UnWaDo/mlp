#include <gtest/gtest.h>

#include "s21_image.h"
#include "s21_image_test.h"

#include <iostream>

TEST_F(ImageTest, TestGrayscaleGrayscaling) {
  // given
  // when
  auto transformed = s21::Image(grayscale);
  transformed.ToGrayscale();

  // then
  ASSERT_EQ(transformed.GetWidth(), grayscale.GetWidth());
  ASSERT_EQ(transformed.GetHeight(), grayscale.GetHeight());
  ASSERT_EQ(transformed.GetBitsPerPixel(), 8);
  for (std::size_t x = 0; x < grayscale.GetWidth(); x++)
    for (std::size_t y = 0; y < grayscale.GetHeight(); y++)
      ASSERT_EQ(grayscale.GetPixel(x, y), transformed.GetPixel(x, y));
}

TEST_F(ImageTest, TestRGBGrayscaling) {
  // given
  auto rgb_to_gs = s21::Image("resource/rgb_to_gs.bmp");

  // when
  auto transformed = s21::Image(rgb);
  transformed.ToGrayscale();
  transformed.ToFile(testing::TempDir() + "output.bmp");
  
  // then
  ASSERT_EQ(transformed.GetWidth(), rgb.GetWidth());
  ASSERT_EQ(transformed.GetHeight(), rgb.GetHeight());
  ASSERT_EQ(transformed.GetBitsPerPixel(), 8);
  for (std::size_t x = 0; x < rgb.GetWidth(); x++)
    for (std::size_t y = 0; y < rgb.GetHeight(); y++)
      ASSERT_EQ(rgb_to_gs.GetPixel(x, y), transformed.GetPixel(x, y));
}
