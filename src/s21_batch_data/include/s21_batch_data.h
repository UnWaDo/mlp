#ifndef CPP7_MLP_1_SRC_S21_BATCH_DATA_INCLUDE_BATCH_DATA_H_
# define CPP7_MLP_1_SRC_S21_BATCH_DATA_INCLUDE_BATCH_DATA_H_

# include <string>
# include <vector>
# include <fstream>
# include <functional>
# include "s21_perceptron.h"
# include "s21_matrix.h"
# include <ctime>

# define DEFAULT_MAX_STEPS  100

namespace s21 {

  struct DataSample {

    DataSample(Matrix& input, std::size_t target);
    DataSample(const Matrix& input, std::size_t target);

    Matrix GetTargetRepresentation(std::size_t classes_number);

    const Matrix& input;
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

    friend std::ostream& operator<<(std::ostream&, PredictionResult&);
  };

  struct MetricValues {

    MetricValues();
    MetricValues(PredictionResult& result);

    float accuracy;
    float precision;
    float recall;
    float f_measure;

    MetricValues& operator+=(MetricValues&);
    MetricValues& operator/=(std::size_t&);

    friend std::ostream& operator<<(std::ostream&, MetricValues&);
  };

  class BatchData {

    public:

      BatchData(std::size_t classes_number, std::size_t input_length);
      BatchData(const std::string& filename);

      void LoadData(const std::string& path);
      void PurgeData();
      void ShuffleData();

      std::size_t Predict(Perceptron&, std::size_t id) const;

      // void Train(Perceptron&) const;
      void Train(Perceptron& perceptron,
                 std::function<void(std::size_t, MetricValues)> f = nullptr,
                 bool *do_continue = nullptr) const;
      void Train(Perceptron&, std::size_t k, std::size_t batch_id) const;

      MetricValues Validate(Perceptron&) const;
      MetricValues Validate(Perceptron&, std::size_t start_id, std::size_t end_id) const;
      MetricValues KCrossValidation(Perceptron&, std::size_t k);

      std::size_t GetClassesNumber() const;
      std::size_t GetInputLength() const;

      DataSample GetRandomSample() const;

      std::size_t GetDataSize() const;
      std::size_t GetMaxSteps() const;

      DataSample GetSample(std::size_t n) const;

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

#endif // CPP7_MLP_1_SRC_S21_BATCH_DATA_INCLUDE_BATCH_DATA_H_
