#include "s21_batch_data.h"
#include <random>
#include <stdexcept>

using namespace s21;

Matrix DataSample::GetTargetRepresentation(std::size_t classes_number) {
  float *target_repr = new float[classes_number];
  for (std::size_t i = 0; i < classes_number; i++)
    target_repr[i] = 0;
  target_repr[target] = 1;
  return Matrix(1, int(classes_number), target_repr);
}

std::size_t BatchData::GetClassesNumber() {
  return classes_number_;
}

std::size_t BatchData::GetInputLength() {
  return input_length_;
}

DataSample BatchData::GetRandomSample() {
  std::random_device r;
  std::mt19937 engine(r());
  std::uniform_int_distribution<std::mt19937::result_type> dist(0, input_data_.size() - 1);
  std::size_t id = dist(engine);
  return GetSample(id);
}

std::size_t BatchData::GetDataSize() {
  return classes_.size();
}

std::size_t s21::BatchData::GetMaxSteps() {
  return max_steps_;
}

DataSample BatchData::GetSample(std::size_t n) {
  if (n >= GetDataSize())
    throw std::runtime_error("Buffer oveflow during accesing sample");
  std::size_t true_index = indices_[n];
  return {input_data_[true_index], classes_[true_index]};
}

void s21::BatchData::SetMaxSteps(std::size_t max_steps) {
  max_steps_ = max_steps;
}
