#include "s21_batch_data.h"

using namespace s21;

std::size_t BatchData::Predict(Perceptron &Perceptron, std::size_t id) const {

  auto data = GetSample(id);
  auto result = Perceptron.ForwardPropagation(data.input);

  std::size_t max_idx = 0;

  for (std::size_t i = 1; i < GetClassesNumber(); i++) {

    if (result[0][i] > result[0][max_idx]) {
      max_idx = i;
    }
  }

  return max_idx;
}

MetricValues BatchData::Validate(Perceptron& perceptron) const {

  auto predicted = PredictionResult(GetClassesNumber());

  for (std::size_t i = 0; i < GetDataSize(); i++) {

    auto sample_prediction = Predict(perceptron, i);
    predicted.AddResult(GetSample(i).target, sample_prediction);
  }

  return {predicted};
}

MetricValues BatchData::Validate(Perceptron &perceptron, std::size_t start_id, std::size_t end_id) const {

  if (end_id > GetDataSize()) {
    end_id = GetDataSize();
  }

  auto predicted = PredictionResult(GetClassesNumber());

  for (std::size_t i = start_id; i < end_id; i++) {

    auto sample_prediction = Predict(perceptron, i);
    predicted.AddResult(GetSample(i).target, sample_prediction);
  }

  return {predicted};
}

MetricValues s21::BatchData::KCrossValidation(Perceptron &perceptron, std::size_t k) {

  if (k == 0 || k > GetDataSize())
    throw std::runtime_error("Invalid k for k-cross validation (must be 0 < k <= data_size)");

  ShuffleData();

  auto batch_size = GetDataSize() / k;

  MetricValues metric;

  for (std::size_t batch_id = 0; batch_id < k; batch_id++) {

    Train(perceptron, k, batch_id);

    auto batch_metric = Validate(
      perceptron,
      batch_id * batch_size,
      (batch_id + 1) * batch_size
    );
    metric += batch_metric;
  }

  metric /= k;

  return metric;
}
