#ifndef CPP7_MLP_SRC_S21_IMAGE_TEST_S21_IMAGE_TEST_H_
#define CPP7_MLP_SRC_S21_IMAGE_TEST_S21_IMAGE_TEST_H_

#include <gtest/gtest.h>

#include "s21_image.h"

class ImageTest: public testing::Test {
 protected:

  ImageTest(): 
    bitmap("resource/bitmap.bmp"),
    grayscale("resource/grayscale.bmp"),
    rgb("resource/rgb.bmp") {}

  s21::Image bitmap;
  s21::Image grayscale;
  s21::Image rgb;
};

#endif
