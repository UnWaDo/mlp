#include "s21_image.h"
#include <stdexcept>

void s21::Image::Rescale(std::size_t new_width, std::size_t new_height)
{
  if (new_width * new_height == width_ * height_) {
    width_ = new_width;
    height_ = new_height;
    return ;
  }
  std::size_t scales[2] = {(new_width % width_ + new_width) / width_, 
                           (new_height % height_ + new_height) / height_};
  std::size_t shrinks[2] = {(width_ % new_width + width_) / new_width,
                            (height_ % new_height + height_) / new_height};
  if (!scales[0])
    scales[0] = 1;
  if (!scales[1])
    scales[1] = 1;
  if (!shrinks[0])
    shrinks[0] = 1;
  if (!shrinks[1])
    shrinks[1] = 1;
  std::vector<uint> new_pixels;
  new_pixels.reserve(new_width * new_height);
  std::vector<uint> row;
  row.reserve(new_width);

  auto rect_y_amount = height_ / shrinks[1] * shrinks[1];
  auto rect_x_amount = width_ / shrinks[0] * shrinks[0];

  for (std::size_t rect_y = 0; rect_y < rect_y_amount; rect_y += shrinks[1]) {
    for (std::size_t rect_x = 0; rect_x < rect_x_amount; rect_x += shrinks[0]) {
      uint pixel = 0;
      for (std::size_t sh_x = 0; sh_x < shrinks[0] && rect_x + sh_x < width_; sh_x++) {
        for (std::size_t sh_y = 0; sh_y < shrinks[1] && rect_y + sh_y < height_; sh_y++) {
          pixel += GetPixel(rect_x + sh_x, height_ - (rect_y + sh_y));
        }
      }
      row.insert(row.end(), scales[0], pixel / shrinks[0] / shrinks[1]);
    }
    for (std::size_t sc_y = 0; sc_y < scales[1]; sc_y++) {
      new_pixels.insert(new_pixels.end(), row.begin(), row.end());
    }
    row.clear();
  }
  pixels_ = new_pixels;
  width_ = new_width;
  height_ = new_height;
}
