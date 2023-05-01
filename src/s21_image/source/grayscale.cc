#include "s21_image.h"
#include <cmath>

static double FromGamma(long double relative) {
  if (relative <= 4.045e-2)
    return relative / 12.92;
  return pow((relative + 0.055) / 1.055, 2.4);
}

static double ToGamma(long double relative) {
  if (relative <= 3.1308e-3)
    return relative * 12.92;
  return pow(relative, 1 / 2.4) * 1.055 - 0.055;
}

void s21::Image::ToGrayscale() {
  if (bits_per_pixel_ == 8)
    return ;
  if (bits_per_pixel_ == 1) {
    for (std::size_t i = 0; i < pixels_.size(); i++)
      pixels_[i] *= 255;
    bits_per_pixel_ = 8;
    return ;
  }
  auto scaler = 1 << (bits_per_pixel_ / 3);
  for (std::size_t i = 0; i < pixels_.size(); i++) {
    auto color = pixels_[i];
    double rgb[3];
    for (auto j = 0; j < 3; j++) {
      rgb[j] = FromGamma(1.0 * (color % scaler) / (scaler - 1));
      color /= scaler;
    }
    pixels_[i] = std::round(ToGamma(
      0.2126 * rgb[0] +
      0.7152 * rgb[1] +
      0.0722 * rgb[2]
    ) * (scaler - 1));
  }
  bits_per_pixel_ = 8;
}
