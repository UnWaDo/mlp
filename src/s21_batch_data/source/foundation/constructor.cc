#include <fstream>
#include <stdexcept>

#include "s21_batch_data.h"

using namespace s21;

PredictionResult::PredictionResult(std::size_t classes_number) {

  true_positives.reserve(classes_number);
  true_negatives.reserve(classes_number);
  false_positives.reserve(classes_number);
  false_negatives.reserve(classes_number);

  for (std::size_t i = 0; i < classes_number; i++) {

    true_positives.push_back(0);
    true_negatives.push_back(0);
    false_positives.push_back(0);
    false_negatives.push_back(0);
  }
}

MetricValues::MetricValues() {

  accuracy = 0;
  precision = 0;
  recall = 0;
  f_measure = 0;
}

MetricValues::MetricValues(PredictionResult& result) : MetricValues() {

  auto total = result.true_positives[0] +
    result.true_negatives[0] +
    result.false_positives[0] +
    result.false_negatives[0];

  auto classes_amount = result.true_positives.size();

  for (std::size_t i = 0; i < classes_amount; i++) {

    auto correct = result.true_positives[i] + result.true_negatives[i];
    auto pred_positives = result.true_positives[i] + result.false_positives[i];
    auto real_positives = result.true_positives[i] + result.false_negatives[i];

    if (total != 0)
      accuracy += 1.0 * correct / total;
    if (pred_positives != 0)
      precision += 1.0 * result.true_positives[i] / pred_positives;
    if (real_positives != 0)
      recall += 1.0 * result.true_positives[i] / real_positives;
  }

  accuracy /= classes_amount;
  precision /= classes_amount;
  recall /= classes_amount;
  if (recall != 0 || precision != 0)
    f_measure = 2.0 * recall * precision / (recall + precision);
}

BatchData::BatchData(std::size_t classes_number, std::size_t input_length) {

  classes_number_ = classes_number;
  input_length_ = input_length;
  max_steps_ = DEFAULT_MAX_STEPS;
}

BatchData::BatchData(const std::string& filename) : classes_number_(0), input_length_(0) {

  LoadData(filename);
  max_steps_ = DEFAULT_MAX_STEPS;
}

DataSample::DataSample(Matrix& in, std::size_t target) 
  : input(in)
  , target(target) { }

DataSample::DataSample(const Matrix& in, std::size_t target) 
  : input(in)
  , target(target) { }
