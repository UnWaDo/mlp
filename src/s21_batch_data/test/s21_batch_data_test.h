#ifndef CPP7_MLP_1_SRC_S21_BATCH_DATA_TEST_S21_BATCH_DATA_TEST_H_
# define CPP7_MLP_1_SRC_S21_BATCH_DATA_TEST_S21_BATCH_DATA_TEST_H_

# include <string>
# include <vector>
# include "s21_batch_data.h"
# include "s21_matrix_perceptron.h"

class BatchDataTest: public testing::Test {
protected:

  BatchDataTest():
    data(5, 30),
    perceptron("perceptron_4_30_20_10_5", "resource/")
    { }

  s21::BatchData data;
  MatrixPerceptron perceptron;
};

#endif