#include <fstream>
#include <stdexcept>
#include <cstring>

#include "s21_image.h"

void s21::Image::ToFile(const std::string& filename) {
  std::ofstream out;

  out.open(filename, std::ios::binary | std::ios::trunc);
  if (!out.is_open())
    throw std::runtime_error("file " + filename + " cannot be opened for writing");
  BMPHeader header(*this);
  out.write(reinterpret_cast<char *>(&header), sizeof(header));
  if (out.fail())
    throw std::runtime_error("failed to write");
  auto palette_length(header.colors_used * (bits_per_pixel_ <= 8));
  char colors[4] = {0, 0, 0, 0};
  for (uint i = 0; i < palette_length; i++) {
    colors[0] = i;
    colors[1] = i;
    colors[2] = i;
    out.write(reinterpret_cast<char *>(colors), 4);
  }
  auto bytes_per_row(width_ * bits_per_pixel_ / 8);
  if (bytes_per_row % 4)
    bytes_per_row = (bytes_per_row / 4 + 1) * 4;
  char *buffer = new char[bytes_per_row];
  for (std::size_t y = 0; y < height_; y++) {
    std::memset(buffer, 0, width_ * bits_per_pixel_ / 8);
    for (std::size_t first_bit = 0; first_bit < width_ * bits_per_pixel_; first_bit += bits_per_pixel_) {
      uint pixel_value = pixels_[first_bit / bits_per_pixel_ + y * width_];
      if (bits_per_pixel_ < 8) {
        buffer[first_bit / 8] += (
          (unsigned char)(pixel_value)
        ) << (8 - bits_per_pixel_);
      }
      for (std::size_t byte = 0; byte < bits_per_pixel_ / 8; byte++) {
        buffer[(first_bit + bits_per_pixel_) / 8 - byte - 1] = pixel_value % 256;
        pixel_value /= 256;
      }
    }
    out.write(buffer, bytes_per_row);
    if (out.fail()) {
      delete[] buffer;
      throw std::runtime_error("error while writing to a file");
    }
  }
  delete[] buffer;
  char end[2] = {0, 0};
  out.write(reinterpret_cast<char *>(end), 2);
}