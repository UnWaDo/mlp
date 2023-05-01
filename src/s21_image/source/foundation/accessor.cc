#include "s21_image.h"

std::size_t s21::Image::GetWidth() {
    return width_;
}

std::size_t s21::Image::GetHeight() {
  return height_;
}

std::size_t s21::Image::GetBitsPerPixel() {
  return bits_per_pixel_;
}

uint s21::Image::GetPixel(std::size_t x, std::size_t y) {
  if (width_ == 0 || height_ == 0)
    return 0;
  std::size_t position = (height_ - 1 - y % height_) * width_ + (x % width_);
  return pixels_[position];
}
