#include "s21_batch_data.h"

using namespace s21;

void BatchData::Train(Perceptron &perceptron) {
  auto classes_number = GetClassesNumber();
  for (std::size_t steps = 0; steps < max_steps_; steps++) {
    for (std::size_t i = 0; i < GetDataSize(); i++) {
      auto sample = GetSample(i);
      perceptron.BackPropagation(
        sample.input,
        sample.GetTargetRepresentation(classes_number)
      );
    }
  }
}

void BatchData::Train(Perceptron &perceptron, std::size_t k, std::size_t batch_id) {
  auto batch_size = GetDataSize() / k;
  auto classes_number = GetClassesNumber();
  for (std::size_t steps = 0; steps < max_steps_; steps++) {
    for (std::size_t i = 0; i < batch_id * batch_size; i++) {
      auto sample = GetSample(i);
      perceptron.BackPropagation(
        sample.input,
        sample.GetTargetRepresentation(classes_number)
      );
    }
    for (std::size_t i = (batch_id + 1) * batch_size; i < GetDataSize(); i++) {
      auto sample = GetSample(i);
      perceptron.BackPropagation(
        sample.input,
        sample.GetTargetRepresentation(classes_number)
      );
    }
  }
}