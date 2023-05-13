#include "s21_image.h"
#include "s21_image_test.h"
#include "s21_matrix.h"

TEST_F(ImageTest, TestImageToVectorConversionBitmap) {
  // given
  float pixels[] = {
    1, 0, 1, 0, 1,
    0, 0, 0, 0, 0,
    1, 0, 1, 0, 0,
    0, 0, 0, 0, 0,
    1, 0, 1, 0, 1,
  };
  auto n = sizeof(pixels) / sizeof(*pixels);

  // when
  float *values = new float[n];
  for (std::size_t i = 0; i < n; i++)
    values[i] = 1 - pixels[i] / 1;
  auto expected = Matrix(1, n, values);
  auto from_img = bitmap.ToVector();

  // then
  ASSERT_EQ(expected.m(), from_img.m());
  ASSERT_EQ(expected.n(), from_img.n());
  for (std::size_t i = 0; i < n; i++)
    ASSERT_NEAR(expected[0][i], from_img[0][i], 1e-4);
}

TEST_F(ImageTest, TestImageToVectorConversionGrayscale) {
  // given
  float pixels[] = {
      0, 255, 118, 255,   0,
    255, 255, 255, 255, 255,
    118, 255,  57, 255, 118,
    255, 255, 255, 255, 255,
      0, 255, 118, 255,   0
  };
  auto n = sizeof(pixels) / sizeof(*pixels);

  // when
  float *values = new float[n];
  for (std::size_t i = 0; i < n; i++)
    values[i] = 1 - pixels[i] / 255;
  auto expected = Matrix(1, n, values);
  auto from_img = grayscale.ToVector();

  // then
  ASSERT_EQ(expected.m(), from_img.m());
  ASSERT_EQ(expected.n(), from_img.n());
  for (std::size_t i = 0; i < n; i++)
    ASSERT_NEAR(expected[0][i], from_img[0][i], 1e-4);
}

TEST_F(ImageTest, TestImageToVectorConversionRGB) {
  // given
  float pixels[] = {
    127, 255, 247, 255, 166,
    255, 255, 255, 255, 255,
    220, 255, 145, 255, 228,
    255, 255, 255, 255, 255,
     76, 255, 229, 255, 142
  };
  auto n = sizeof(pixels) / sizeof(*pixels);

  // when
  float *values = new float[n];
  for (std::size_t i = 0; i < n; i++)
    values[i] = 1 - pixels[i] / 255;
  auto expected = Matrix(1, n, values);
  rgb.ToGrayscale();
  auto from_img = rgb.ToVector();

  // then
  ASSERT_EQ(expected.m(), from_img.m());
  ASSERT_EQ(expected.n(), from_img.n());
  for (std::size_t i = 0; i < n; i++)
    ASSERT_NEAR(expected[0][i], from_img[0][i], 1e-4);
}

TEST_F(ImageTest, TestImageToVectorConversionAsymGrayscale) {
  // given
  float pixels[] = {
      0, 255, 118,  52,   0,
    255,  52, 255, 255,  52,
    118, 255,  57, 255, 118,
    255, 255, 255,  52, 255,
      0, 255, 118, 255,   0
  };
  auto n = sizeof(pixels) / sizeof(*pixels);
  auto img = s21::Image("resource/grayscale_asym.bmp");

  // when
  float *values = new float[n];
  for (std::size_t i = 0; i < n; i++)
    values[i] = 1 - pixels[i] / 255;
  auto expected = Matrix(1, n, values);
  auto from_img = img.ToVector();

  // then
  ASSERT_EQ(expected.m(), from_img.m());
  ASSERT_EQ(expected.n(), from_img.n());
  for (std::size_t i = 0; i < n; i++) {
    ASSERT_NEAR(expected[0][i], from_img[0][i], 1e-4);
  }
}
