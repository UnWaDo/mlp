//
// Created by Anton Ivanov on 06.05.2023.
//

#include <QApplication>

#include "s21_windows.h"
#include "s21_matrix_perceptron.h"
#include "s21_image.h"

#include <iostream>
#include <ctime>

int main(int argc, char** argv) {

  (void) argc;
  (void) argv;
  // QApplication app(argc, argv);

  // s21::MainWindow window;

  // window.show();
  // return app.exec();

  auto data = s21::BatchData("datasets/emnist-letters-train.csv");
  std::cout << "loaded data" << std::endl;
  auto perceptron = MatrixPerceptron("datasets/lol/", "");
  std::cout << "loaded perceptron" << std::endl;

  // std::cout << "Sample 2" << std::endl;
  // {
  //   auto sample = data.GetSample(2);
  //   std::cout << data.Predict(perceptron, 0) << "\n" << sample.target << std::endl;
  //   std::cout << perceptron.ForwardPropagation(sample.input) << std::endl;
  //   auto t = sample.GetTargetRepresentation(26);
  //   std::cout << t << std::endl;
  //   perceptron.BackPropagation(sample.input, t);
  //   std::cout << perceptron.ForwardPropagation(sample.input) << std::endl;
  // }

  // std::cout << "Sample 0" << std::endl;
  // {
  //   auto sample = data.GetSample(0);
  //   std::cout << data.Predict(perceptron, 0) << "\n" << sample.target << std::endl;
  //   std::cout << perceptron.ForwardPropagation(sample.input) << std::endl;
  //   auto t = sample.GetTargetRepresentation(26);
  //   std::cout << t << std::endl;
  //   perceptron.BackPropagation(sample.input, t);
  //   std::cout << perceptron.ForwardPropagation(sample.input) << std::endl;
  // }
  auto m = data.Validate(perceptron);
  std::cout << m << std::endl;
  auto start = time(nullptr);
  
  data.Train(perceptron, [&](std::size_t e, s21::MetricValues m){
    std::cout << time(nullptr) - start << " " << e << " " << m << std::endl;
  });
  perceptron.ExportPerceptronToFile("lol");
}
