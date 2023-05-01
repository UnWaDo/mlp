#include <gtest/gtest.h>

#include "s21_image.h"
#include "s21_image_test.h"

#include <iostream>

using namespace s21;

TEST_F(ImageTest, GetDimensions) {
  // given
  // when
  // then
  EXPECT_EQ(grayscale.GetWidth(), 5);
  EXPECT_EQ(grayscale.GetHeight(), 5);
}

TEST_F(ImageTest, GetBitsPerPixel) {
  // given
  // when
  // then
  EXPECT_EQ(bitmap.GetBitsPerPixel(), 1);
  EXPECT_EQ(grayscale.GetBitsPerPixel(), 8);
  EXPECT_EQ(rgb.GetBitsPerPixel(), 24);
}

TEST_F(ImageTest, GetPixelsBitmap) {
  // given
  std::vector<uint> pixels({
    1, 0, 1, 0, 1,
    0, 0, 0, 0, 0,
    1, 0, 1, 0, 1,
    0, 0, 0, 0, 0,
    1, 0, 0, 0, 1,
  });

  // when
  // then
  for (std::size_t x = 0; x < 5; x++)
    for (std::size_t y = 0; y < 5; y++)
      ASSERT_EQ(pixels[5 * y + x], bitmap.GetPixel(x, y));
}

TEST_F(ImageTest, GetPixelsGrayscale) {
  // given
  std::vector<uint> pixels({
      0, 255, 118, 255,   0,
    255, 255, 255, 255, 255,
    118, 255,  57, 255, 118,
    255, 255, 255, 255, 255,
      0, 255, 118, 255,   0
  });

  // when
  // then
  for (std::size_t x = 0; x < 5; x++)
    for (std::size_t y = 0; y < 5; y++)
      ASSERT_EQ(pixels[5 * y + x], grayscale.GetPixel(x, y));
}

TEST_F(ImageTest, GetPixelsGrayscaleAsymmetrical) {
  // given
  std::vector<uint> pixels({
      0, 255, 118, 255,   0,
    255,  52, 255, 255, 255,
    118, 255,  57, 255, 118,
     52, 255, 255,  52, 255,
      0,  52, 118, 255,   0
  });

  // when
  auto img = s21::Image("resource/grayscale_asym.bmp");

  // then
  for (std::size_t x = 0; x < 5; x++)
    for (std::size_t y = 0; y < 5; y++)
      ASSERT_EQ(pixels[5 * y + x], img.GetPixel(x, y));
}

TEST_F(ImageTest, GetPixelsRGB) {
  // given
  std::vector<uint> pixels({
    0x0000ff, 0xffffff, 0x00ff00, 0xffffff, 0xff0000,
    0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff,
    0x00ffff, 0xffffff, 0xff00ff, 0xffffff, 0xffff00,
    0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff,
    0x8080ff, 0xffffff, 0x80ff80, 0xffffff, 0xff8080,
  });

  // when
  // then
  for (std::size_t x = 0; x < 5; x++)
    for (std::size_t y = 0; y < 5; y++)
      ASSERT_EQ(pixels[5 * y + x], rgb.GetPixel(x, y));
}
