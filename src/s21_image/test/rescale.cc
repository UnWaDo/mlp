#include <gtest/gtest.h>

#include "s21_image.h"
#include "s21_image_test.h"

TEST_F(ImageTest, TestRescaleToHorizontalRectangle) {
  // given
  auto width = grayscale.GetWidth();
  auto height = grayscale.GetHeight();
  auto upperLeft = grayscale.GetPixel(0, 0);
  auto upperRight = grayscale.GetPixel(width - 1, 0);
  auto lowerLeft = grayscale.GetPixel(0, height - 1);
  auto lowerRight = grayscale.GetPixel(width - 1, height - 1);

  // when
  grayscale.Rescale(width * height, 1);
  
  // then
  ASSERT_EQ(grayscale.GetWidth(), width * height);
  ASSERT_EQ(grayscale.GetHeight(), 1);
  ASSERT_EQ(upperLeft, grayscale.GetPixel(0, 0));
  ASSERT_EQ(upperRight, grayscale.GetPixel(width - 1, 0));
  ASSERT_EQ(lowerLeft, grayscale.GetPixel((width - 1) * height, 0));
  ASSERT_EQ(lowerRight, grayscale.GetPixel(width * height - 1, 0));
}

TEST_F(ImageTest, TestRescaleToVerticalRectangle) {
  // given
  auto width = grayscale.GetWidth();
  auto height = grayscale.GetHeight();
  auto upperLeft = grayscale.GetPixel(0, 0);
  auto upperRight = grayscale.GetPixel(width - 1, 0);
  auto lowerLeft = grayscale.GetPixel(0, height - 1);
  auto lowerRight = grayscale.GetPixel(width - 1, height - 1);

  // when
  grayscale.Rescale(1, width * height);
  
  // then
  ASSERT_EQ(grayscale.GetWidth(), 1);
  ASSERT_EQ(grayscale.GetHeight(), width * height);
  ASSERT_EQ(upperLeft, grayscale.GetPixel(0, 0));
  ASSERT_EQ(upperRight, grayscale.GetPixel(0, width - 1));
  ASSERT_EQ(lowerLeft, grayscale.GetPixel(0, width * (height - 1)));
  ASSERT_EQ(lowerRight, grayscale.GetPixel(0, width * height - 1));
}

TEST_F(ImageTest, TestRescaleWithShrink) {
  // given
  auto width(grayscale.GetWidth());
  auto height(grayscale.GetHeight());

  // when
  uint meanColor = 0;
  for (std::size_t x = 0; x < width; x++) {
    for (std::size_t y = 0; y < height; y++) {
      meanColor += grayscale.GetPixel(x, y);
    }
  }
  meanColor /= width * height;
  grayscale.Rescale(1, 1);
  
  // then
  ASSERT_EQ(grayscale.GetWidth(), 1);
  ASSERT_EQ(grayscale.GetHeight(), 1);
  ASSERT_EQ(meanColor, grayscale.GetPixel(0, 0));
}
