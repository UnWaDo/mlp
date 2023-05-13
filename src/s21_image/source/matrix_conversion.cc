#include "s21_image.h"
#include "s21_matrix.h"


Matrix s21::Image::ToVector() {
  auto matrix = Matrix(1, width_ * height_);
  auto max_color = (1 << bits_per_pixel_) - 1;
  auto data = matrix.data();
  for (std::size_t i = 0; i < width_ * height_; i++) {
    auto y = i / height_;
    auto x = i % height_;
    data[i] = 1.0 - 1.0 * GetPixel(y, x) / max_color;
  }
  return matrix;
}
