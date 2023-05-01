#include <fstream>
#include <stdexcept>
#include <iterator>

#include "s21_image.h"

s21::Image::Image(const std::string& filename) {
  std::ifstream ins;
  ins.open(filename, std::ios::binary);
  if (!ins.is_open())
    throw std::runtime_error("file " + filename + " cannot be opened");
  ins >> std::noskipws;

  BMPHeader header;
  ins.read(reinterpret_cast<char *>(&header), sizeof(header));
  if (ins.fail() || ins.eof() || header.signature != ('M' << 8) + 'B')
    throw std::runtime_error("invalid file header format");
  width_ = header.width;
  height_ = header.height;
  bits_per_pixel_ = header.bits_per_pixel;
  pixels_.reserve(width_ * height_);
  ins.seekg(header.data_offset);
  std::size_t line_width = width_ * bits_per_pixel_ / 8;
  if (line_width % 4 || line_width == 0)
    line_width = (line_width / 4 + 1) * 4;
  unsigned char *buffer = new unsigned char[line_width];
  for (std::size_t y = 0; y < height_; y++) {
    ins.read(reinterpret_cast<char *>(buffer), line_width);
    if (ins.fail() || ins.eof()) {
      delete[] buffer;
      throw std::runtime_error("invalid file body format");
    }
    for (std::size_t first_bit = 0; first_bit < width_ * bits_per_pixel_; first_bit += bits_per_pixel_) {
      uint pixel_value = 0;
      if (bits_per_pixel_ < 8) {
        pixel_value = (
          (unsigned char)(buffer[first_bit / 8] << first_bit)
        ) >> (8 - bits_per_pixel_);
      }
      for (std::size_t byte = 0; byte < bits_per_pixel_ / 8; byte++) {
        pixel_value *= 256;
        pixel_value += buffer[first_bit / 8 + byte];
      }
      pixels_.insert(pixels_.end(), pixel_value);
    }
  }
  delete[] buffer;
}

s21::Image::Image(std::vector<uint>& pixels, std::size_t width, std::size_t height, std::size_t bits_per_pixel)
{
  width_ = width;
  height_ = height;
  bits_per_pixel_ = bits_per_pixel;
  pixels_.insert(pixels_.begin(), pixels.begin(), pixels.end());
}

s21::BMPHeader::BMPHeader(Image& img) {
  signature = ('M' << 8) + 'B';
  reserved = 0;
  size = 40;
  width = img.GetWidth();
  height = img.GetHeight();
  planes = 1;
  bits_per_pixel = img.GetBitsPerPixel();
  compression = 0;
  image_size = 0;
  x_per_meter = 2835;
  y_per_meter = 2835;
  colors_used = 1 << bits_per_pixel;
  // 14 (file header) + 40 (image header) + 4 * colors_used if bits_per_pixel is less than 8
  data_offset = 54 + 4 * colors_used * (bits_per_pixel <= 8);
  auto bytes_per_row(width);
  if (bytes_per_row % 4)
    bytes_per_row = (bytes_per_row / 4 + 1) * 4;
  filesize = data_offset + bytes_per_row * height + 2;
  important_colors = 0;
}
