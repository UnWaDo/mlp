#ifndef CPP7_MLP_1_SRC_S21_BATCH_DATA_INCLUDE_BATCH_DATA_H_
# define CPP7_MLP_1_SRC_S21_BATCH_DATA_INCLUDE_BATCH_DATA_H_

# include <string>
# include <vector>
# include <fstream>
# include "s21_perceptron.h"
# include "s21_matrix.h"
# include <ctime>

# define DEFAULT_MAX_STEPS  100

namespace s21 {
  struct DataSample {
    DataSample(Matrix& input, std::size_t target);
    Matrix GetTargetRepresentation(std::size_t classes_number);
    Matrix& input;
    std::size_t target;
  };

  struct PredictionResult {
    PredictionResult(std::size_t classes_number);
    void AddResult(std::size_t target_class, Matrix& result);
    void AddResult(std::size_t target_class, std::size_t result_class);
    std::vector<std::size_t> true_positives;
    std::vector<std::size_t> true_negatives;
    std::vector<std::size_t> false_positives;
    std::vector<std::size_t> false_negatives;
    friend std::ostream& operator<<(std::ostream& out, PredictionResult& bd);
  };

  struct MetricValues {
    MetricValues();
    MetricValues(PredictionResult& result);
    float accuracy;
    float precision;
    float recall;
    float f_measure;
    std::time_t time_spent;
    MetricValues& operator+=(MetricValues& other);
    MetricValues& operator/=(std::size_t& other);
    friend std::ostream& operator<<(std::ostream& out, MetricValues& bd);
  };

  class BatchData {
    public:
      BatchData(std::size_t classes_number, std::size_t input_length);
      BatchData(const std::string& filename);

      void LoadData(const std::string& path);
      void PurgeData();
      void ShuffleData();
      std::size_t Predict(Perceptron& Perceptron, std::size_t id);
      void Train(Perceptron& perceptron);
      void Train(Perceptron& perceptron, void (*f)(std::size_t e, MetricValues m));
      void Train(Perceptron& perceptron, std::size_t k, std::size_t batch_id);
      MetricValues Validate(Perceptron& perceptron);
      MetricValues Validate(Perceptron& perceptron, std::size_t start_id, std::size_t end_id);
      MetricValues KCrossValidation(Perceptron& perceptron, std::size_t k);
      std::size_t GetClassesNumber();
      std::size_t GetInputLength();
      DataSample GetRandomSample();
      std::size_t GetDataSize();
      std::size_t GetMaxSteps();
      DataSample GetSample(std::size_t n);
      void SetMaxSteps(std::size_t max_steps);
      friend std::ifstream& operator>>(std::ifstream& in, BatchData& bd);

    private:
      std::vector<std::size_t> indices_;
      std::vector<Matrix> input_data_;
      std::vector<std::size_t> classes_;
      std::size_t classes_number_;
      std::size_t input_length_;
      std::size_t max_steps_;
  };
}

#endif