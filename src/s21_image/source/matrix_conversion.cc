#include "s21_image.h"
#include "s21_matrix.h"


s21::Matrix s21::Image::ToVector() {

  auto matrix = Matrix(1, width_ * height_);

  uint max_color = 0;
  for (std::size_t x = 0; x < width_; x++) {

    for (std::size_t y = 0; y < height_; y++) {

      if (GetPixel(x, y) > max_color)
        max_color = GetPixel(x, y);
    }
  }

  auto data = matrix.data();

  for (std::size_t i = 0; i < width_ * height_; i++) {

    auto y = i / height_;
    auto x = i % height_;
    data[i] = 1.0 - 1.0 * GetPixel(y, x) / max_color;
  }
  return matrix;
}
