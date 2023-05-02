#include "s21_batch_data.h"

using namespace s21;

void BatchData::LoadData(const std::string &filename) {
  std::ifstream ins(filename);
  if (!ins.is_open())
    throw std::runtime_error("file " + filename + " cannot be opened");
  while (!ins.eof() && !ins.fail()) {
    ins >> *this;
  }
  if (classes_number_)
    return ;
  std::size_t max_class = 0;
  for (std::size_t i = 0; i < classes_.size(); i++) {
    if (classes_[i] > max_class)
      max_class = classes_[i];
  }
  classes_number_ = std::size_t(max_class + 1);
}

void BatchData::PurgeData() {
  indices_.clear();
  input_data_.clear();
  classes_.clear();
}
