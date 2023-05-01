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

TEST_F(ImageTest, TestRescaleWithSquareExpansion) {
  // given
  auto width = grayscale.GetWidth();
  auto height = grayscale.GetHeight();
  auto upperLeft = grayscale.GetPixel(0, 0);
  auto upperRight = grayscale.GetPixel(width - 1, 0);
  auto lowerLeft = grayscale.GetPixel(0, height - 1);
  auto lowerRight = grayscale.GetPixel(width - 1, height - 1);
  std::size_t scale_width = 2;
  std::size_t scale_height = 2;

  // when
  grayscale.Rescale(width * scale_width, height * scale_height);
  
  // then
  ASSERT_EQ(grayscale.GetWidth(), width * scale_width);
  ASSERT_EQ(grayscale.GetHeight(), height * scale_height);
  for (std::size_t i = 0; i < scale_width; i++) {
    for (std::size_t j = 0; j < scale_height; j++) {
      ASSERT_EQ(upperLeft, grayscale.GetPixel(0 + i, 0 + j));
      ASSERT_EQ(upperRight, grayscale.GetPixel(scale_width * width - scale_width + i, 0 + j));
      ASSERT_EQ(lowerLeft, grayscale.GetPixel(0 + i, scale_height * height - scale_height + j));
      ASSERT_EQ(lowerRight, grayscale.GetPixel(scale_width * width - scale_width + i, scale_height * height - scale_height + j));
    }
  }
}

TEST_F(ImageTest, TestRescaleWithRectangularExpansion) {
  // given
  auto width = grayscale.GetWidth();
  auto height = grayscale.GetHeight();
  auto upperLeft = grayscale.GetPixel(0, 0);
  auto upperRight = grayscale.GetPixel(width - 1, 0);
  auto lowerLeft = grayscale.GetPixel(0, height - 1);
  auto lowerRight = grayscale.GetPixel(width - 1, height - 1);
  std::size_t scale_width = 3;
  std::size_t scale_height = 2;

  // when
  grayscale.Rescale(width * scale_width, height * scale_height);
  
  // then
  ASSERT_EQ(grayscale.GetWidth(), width * scale_width);
  ASSERT_EQ(grayscale.GetHeight(), height * scale_height);
  for (std::size_t i = 0; i < scale_width; i++) {
    for (std::size_t j = 0; j < scale_height; j++) {
      ASSERT_EQ(upperLeft, grayscale.GetPixel(0 + i, 0 + j));
      ASSERT_EQ(upperRight, grayscale.GetPixel(scale_width * width - scale_width + i, 0 + j));
      ASSERT_EQ(lowerLeft, grayscale.GetPixel(0 + i, scale_height * height - scale_height + j));
      ASSERT_EQ(lowerRight, grayscale.GetPixel(scale_width * width - scale_width + i, scale_height * height - scale_height + j));
    }
  }
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

TEST_F(ImageTest, TestRescaleWithHorizontalExpansion) {
  // given
  auto width = grayscale.GetWidth();
  auto height = grayscale.GetHeight();
  auto upperLeft = grayscale.GetPixel(0, 0);
  auto upperRight = grayscale.GetPixel(width - 1, 0);
  auto lowerLeft = grayscale.GetPixel(0, height - 1);
  auto lowerRight = grayscale.GetPixel(width - 1, height - 1);
  std::size_t scale = 2;

  // when
  grayscale.Rescale(width * scale, height);
  
  // then
  ASSERT_EQ(grayscale.GetWidth(), width * scale);
  ASSERT_EQ(grayscale.GetHeight(), height);
  for (std::size_t i = 0; i < scale; i++) {
    ASSERT_EQ(upperLeft, grayscale.GetPixel(0 + i, 0));
    ASSERT_EQ(upperRight, grayscale.GetPixel(scale * width - scale + i, 0));
    ASSERT_EQ(lowerLeft, grayscale.GetPixel(0 + i, height - 1));
    ASSERT_EQ(lowerRight, grayscale.GetPixel(scale * width - scale + i, height - 1));
    ASSERT_NE(upperLeft, grayscale.GetPixel(0 + i, 1));
    ASSERT_NE(upperRight, grayscale.GetPixel(scale * width - scale + i, 1));
    ASSERT_NE(lowerLeft, grayscale.GetPixel(0 + i, height - 2));
    ASSERT_NE(lowerRight, grayscale.GetPixel(scale * width - scale + i, height - 2));
  }
}

TEST_F(ImageTest, TestRescaleWithVerticalExpansion) {
  // given
  auto width = grayscale.GetWidth();
  auto height = grayscale.GetHeight();
  auto upperLeft = grayscale.GetPixel(0, 0);
  auto upperRight = grayscale.GetPixel(width - 1, 0);
  auto lowerLeft = grayscale.GetPixel(0, height - 1);
  auto lowerRight = grayscale.GetPixel(width - 1, height - 1);
  std::size_t scale = 2;

  // when
  grayscale.Rescale(width, height * scale);
  
  // then
  ASSERT_EQ(grayscale.GetWidth(), width);
  ASSERT_EQ(grayscale.GetHeight(), height * scale);
  for (std::size_t i = 0; i < scale; i++) {
    ASSERT_EQ(upperLeft, grayscale.GetPixel(0, 0 + i));
    ASSERT_EQ(upperRight, grayscale.GetPixel(width - 1, 0 + i));
    ASSERT_EQ(lowerLeft, grayscale.GetPixel(0, scale * height - scale + i));
    ASSERT_EQ(lowerRight, grayscale.GetPixel(width - 1, scale * height - scale + i));
    ASSERT_NE(upperLeft, grayscale.GetPixel(1, 0 + i));
    ASSERT_NE(upperRight, grayscale.GetPixel(width - 2, 0 + i));
    ASSERT_NE(lowerLeft, grayscale.GetPixel(1, scale * height - scale + i));
    ASSERT_NE(lowerRight, grayscale.GetPixel(width - 2, scale * height - scale + i));
  }
}

TEST_F(ImageTest, TestWidthExpansionAndHeightShrinking) {
  // given
  std::size_t initial_width = 6;
  std::size_t initil_height = 4;
  std::vector<uint> initial_pixels = {
    255, 255, 255, 255, 255, 255,
      0, 255,   0, 255,   0, 255,
    255,   0, 255,   0, 255,   0,
      0,   0,   0,   0,   0,   0
  };
  std::size_t result_width = 18;
  std::size_t result_height = 2;
  std::vector<uint> result_pixels = {
    127, 127, 127, 255, 255, 255, 127, 127, 127, 255, 255, 255, 127, 127, 127, 255, 255, 255,
    127, 127, 127,   0,   0,   0, 127, 127, 127,   0,   0,   0, 127, 127, 127,    0,  0,   0,
  };

  // when
  auto initial = s21::Image(initial_pixels, initial_width, initil_height, 8);
  initial.Rescale(result_width, result_height);

  // then
  ASSERT_EQ(initial.GetWidth(), result_width);
  ASSERT_EQ(initial.GetHeight(), result_height);
  for (std::size_t x = 0; x < result_width; x++)
    for (std::size_t y = 0; y < result_height; y++)
      ASSERT_EQ(result_pixels[result_width * y + x], initial.GetPixel(x, y));
}

TEST_F(ImageTest, TestHeightExpansionAndWidthShrinking) {
  // given
  std::size_t initial_width = 6;
  std::size_t initil_height = 4;
  std::vector<uint> initial_pixels = {
    255, 255, 255, 255, 255, 255,
      0, 255,   0, 255,   0, 255,
    255,   0, 255,   0, 255,   0,
      0,   0,   0,   0,   0,   0
  };
  std::size_t result_width = 3;
  std::size_t result_height = 16;
  std::vector<uint> result_pixels = {
    255, 255, 255,
    255, 255, 255,
    255, 255, 255,
    255, 255, 255,
    127, 127, 127,
    127, 127, 127,
    127, 127, 127,
    127, 127, 127,
    127, 127, 127,
    127, 127, 127,
    127, 127, 127,
    127, 127, 127,
      0,   0,   0,
      0,   0,   0,
      0,   0,   0,
      0,   0,   0,
  };

  // when
  auto initial = s21::Image(initial_pixels, initial_width, initil_height, 8);
  initial.Rescale(result_width, result_height);

  // then
  ASSERT_EQ(initial.GetWidth(), result_width);
  ASSERT_EQ(initial.GetHeight(), result_height);
  for (std::size_t x = 0; x < result_width; x++)
    for (std::size_t y = 0; y < result_height; y++)
      ASSERT_EQ(result_pixels[result_width * y + x], initial.GetPixel(x, y));
}
// TODO: Shrink with fraction
// TODO: Shrink by sides