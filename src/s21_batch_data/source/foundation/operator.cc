#include "s21_batch_data.h"
#include <algorithm>
#include <sstream>
#include <iostream>

namespace s21 {
    std::ostream &operator<<(std::ostream &out, PredictionResult &bd) {
      for (std::size_t i = 0; i < bd.true_negatives.size(); i++) {
        out << "Class " << i << std::endl;
        out << "TP " << bd.true_positives[i] << " TN " << bd.true_negatives[i] << std::endl;
        out << "FN " << bd.false_negatives[i] << " FP " << bd.false_positives[i] << std::endl;
      }
      return out;
    }

  std::ostream & operator<<(std::ostream & out, MetricValues& bd){
    out << "accuracy: " << bd.accuracy << ", precision: " << bd.precision;
    out << ", recall: " << bd.recall << ", f-measure: " << bd.f_measure;
    return out;
  }

  std::ifstream &operator>>(std::ifstream &in, BatchData& bd) {
      std::string line;
      std::getline(in, line, '\n');
      if (line.size() == 0)
        return in;
      auto entries = std::count(line.begin(), line.end(), ',');
      if (!bd.input_length_)
        bd.input_length_ = entries;
      if (bd.input_length_ && long(bd.input_length_) != entries) {
        std::stringstream ss;
        ss << "Invalid number of entries: expected " << bd.input_length_ << ", given " << entries;
        throw std::runtime_error(ss.str());
      }
      std::replace(line.begin(), line.end(), ',', ' ');
      std::stringstream stream(line);
      int class_name;
      stream >> class_name;
      if (class_name <= 0 || (bd.classes_number_ && std::size_t(class_name) > bd.classes_number_)) {
        std::stringstream ss;
        ss << "Invalid classname " << class_name;
        throw std::runtime_error(ss.str());
      }
      bd.classes_.push_back(class_name - 1);
      bd.input_data_.emplace_back(1, (int) bd.input_length_);
      bd.indices_.push_back(bd.indices_.size());
      for (std::size_t i = 0; i < bd.input_length_; i++) {
        uint value = 1000;
        stream >> value;
        if (stream.fail() || value > 255) {
          throw std::runtime_error("Error during line parsing");
        }
        bd.input_data_.back()[0][i] = 1.0 * value / 255;
      }
      return in;
  }
}

using namespace s21;

MetricValues& MetricValues::operator+=(MetricValues &other){
  accuracy += other.accuracy;
  precision += other.precision;
  recall += other.recall;
  f_measure += other.f_measure;
  time_spent += other.time_spent;
  return *this;
}

MetricValues& MetricValues::operator/=(std::size_t& other){
  accuracy /= other;
  precision /= other;
  recall /= other;
  f_measure /= other;
  time_spent /= other;
  return *this;
}

void PredictionResult::AddResult(std::size_t target_class, Matrix &result) {
  if ((target_class >= false_negatives.size()) ||
      (std::size_t(result.n()) != false_negatives.size()) ||
      (result.m() != 1))
    throw std::runtime_error("Invalid shape of input data");

  std::size_t max_idx_res = 0;
  for (std::size_t i = 1; i < false_negatives.size(); i++) {
    if (result[0][i] > result[0][max_idx_res])
      max_idx_res = i;
  }
  for (std::size_t i = 0; i < false_negatives.size(); i++) {
    true_positives[i] += (i == max_idx_res) && (i == target_class);
    false_positives[i] += (i == max_idx_res) && (i != target_class);
    false_negatives[i] += (i != max_idx_res) && (i == target_class);
    true_negatives[i] += (i != max_idx_res) && (i != target_class);
  }
}

void PredictionResult::AddResult(std::size_t target_class, std::size_t result_class) {
  if ((target_class >= false_negatives.size()) ||
      (result_class >= false_negatives.size()))
    throw std::runtime_error("Invalid shape of input data");
  for (std::size_t i = 0; i < false_negatives.size(); i++) {
    true_positives[i] += (i == result_class) && (i == target_class);
    false_positives[i] += (i == result_class) && (i != target_class);
    false_negatives[i] += (i != result_class) && (i == target_class);
    true_negatives[i] += (i != result_class) && (i != target_class);
  }
}
