#include "s21_image.h"
#include "s21_matrix.h"


Matrix s21::Image::ToVector() {
  auto matrix = Matrix(1, width_ * height_);
  auto max_color = (1 << bits_per_pixel_) - 1;
  auto data = matrix[0];
  for (std::size_t y = 0; y < height_; y++) {
    for (std::size_t x = 0; x < width_; x++) {
      data[x * height_ + y] = 1.0 - 1.0 * GetPixel(x, y) / max_color;
    }
  }
  return matrix;
}
