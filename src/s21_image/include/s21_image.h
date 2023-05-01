#ifndef CPP7_MLP_SRC_S21_IMAGE_INCLUDE_S21_IMAGE_
# define CPP7_MLP_SRC_S21_IMAGE_INCLUDE_S21_IMAGE_

#include <string>
#include <vector>
#include "s21_matrix.h"

namespace s21 {
  class Image {
  public:
    Image(const std::string& filename);
    Image(
      std::vector<uint>& pixels,
      std::size_t width,
      std::size_t height,
      std::size_t bits_per_pixel
    );
    void Rescale(std::size_t new_width, std::size_t new_height);
    void ToGrayscale();
    Matrix ToVector();
    std::size_t GetWidth();
    std::size_t GetHeight();
    std::size_t GetBitsPerPixel();
    uint GetPixel(std::size_t x, std::size_t y);
    void ToFile(const std::string& filename);

  private:
    std::size_t width_;
    std::size_t height_;
    std::size_t bits_per_pixel_;
    std::vector<uint> pixels_;
  };
  
  #pragma pack(push, 1)
  struct BMPHeader {
    inline BMPHeader() {};
    BMPHeader(Image& img);
    uint16_t signature;
    uint32_t filesize;
    uint32_t reserved;
    uint32_t data_offset;
    uint32_t size;
    uint32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bits_per_pixel;
    uint32_t compression;
    uint32_t image_size;
    uint32_t x_per_meter;
    uint32_t y_per_meter;
    uint32_t colors_used;
    uint32_t important_colors;
  };
  #pragma pack(pop)
}

#endif