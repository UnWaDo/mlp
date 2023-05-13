#include "s21_main_model.h"
#include "s21_matrix_perceptron.h"
#include "s21_graph_perceptron.h"
#include "s21_image.h"

#include <thread>
#include <iostream>
#include <functional>
#include <QInputDialog>
#include <QMessageBox>

s21::MainModel::MainModel(QObject *parent)
    : QObject(parent)
    , perceptron_(nullptr)
    , data_(26, 784) {

  perceptron_params_.number_of_layers = 4;
  perceptron_params_.alpha = 0.1f;
  perceptron_params_.activation_name = "Sigmoid";

  perceptron_params_.number_of_neurons_in_layer = new int[4];
  perceptron_params_.number_of_neurons_in_layer[0] = 784;
  perceptron_params_.number_of_neurons_in_layer[1] = 20;
  perceptron_params_.number_of_neurons_in_layer[2] = 20;
  perceptron_params_.number_of_neurons_in_layer[3] = 26;

  perceptron_type_ = "Matrix";

  InitializePerceptron();
}

s21::MainModel::~MainModel() {
  delete perceptron_;
}

std::size_t s21::MainModel::GetDataSize() const {
  return data_.GetDataSize();
}

void s21::MainModel::PredictImage(QString path) {

  if (path == nullptr)
    return ;

  s21::Image *image;
  try {
    image = new s21::Image(path.toStdString());
  }
  catch (...) {
    emit InvalidPath(path);
    return ;
  }


  image->Rescale(28, 28);
  image->ToGrayscale();

  auto prediction = perceptron_->ForwardPropagation(image->ToVector());

  int max_idx = 0;
  for (int i = 0; i < prediction.n(); i++) {

    if (prediction[0][i] > prediction[0][max_idx])
      max_idx = i;
  }

  delete image;

  emit ImagePredicted('a' + max_idx);
}

void s21::MainModel::SetPerceptronParameters(Perceptron::Parameters& params, std::string_view type) {

  if (perceptron_params_.number_of_layers) {
    delete[] perceptron_params_.number_of_neurons_in_layer;
  }
  perceptron_params_ = params;
  perceptron_type_ = type;
  InitializePerceptron();
}

void s21::MainModel::InitializePerceptron()
{

  Perceptron *new_perceptron = nullptr;

  if (perceptron_type_ == "Matrix")
    new_perceptron = new MatrixPerceptron(perceptron_params_);
  // else
  //   new_perceptron = new GraphPerceptron(perceptron_params_);

  if (perceptron_ != nullptr)
    delete perceptron_;
  perceptron_ = new_perceptron;

  emit PerceptronModified(perceptron_params_, perceptron_type_);
}

void s21::MainModel::LoadPerceptron(QString path) {

  Perceptron *new_perceptron;

  if (path == nullptr)
    return ;

  try {
    if (perceptron_type_ == "Matrix")
      new_perceptron = new MatrixPerceptron(path.toStdString(), "");
    else
      new_perceptron = new GraphPerceptron(path.toStdString(), "");
  }
  catch (...) {
    emit InvalidPath(path);
    return ;
  }
  delete perceptron_;
  perceptron_ = new_perceptron;

  std::cout << "modified" << std::endl;
  emit PerceptronModified(perceptron_params_, perceptron_type_);
}

void s21::MainModel::LoadData(QString path) {

  if (path == nullptr)
    return ;

  try {
    data_.LoadData(path.toStdString());
  }
  catch (...) {
    emit InvalidPath(path);
    return ;
  }
  emit DataLoaded(path, data_);
}

void s21::MainModel::CleanData() {
  data_.PurgeData();
  emit DataCleaned();
}

void s21::MainModel::LaunchTraining(std::size_t epochs, bool *do_continue) {

  std::time_t start;
  std::time(&start);

  data_.SetMaxSteps(epochs);

  std::cout << "Учусь" << std::endl;

  data_.Train(*perceptron_, [&](std::size_t e, s21::MetricValues m){
    std::cout << e << " " << m << std::endl;
    emit IterationPassed(e, m);
  }, do_continue);

  auto m = data_.Validate(*perceptron_);

  emit TrainingFinished(std::time(nullptr) - start, m);

  if (do_continue != nullptr)
    delete do_continue;
}

void s21::MainModel::LaunchCrossValidation(std::size_t k, std::size_t epochs,
                                           bool *do_continue) {

  std::time_t start;
  std::time(&start);

  data_.SetMaxSteps(epochs);

  MetricValues average;

  data_.KCrossValidation(*perceptron_, k, [&](std::size_t e, s21::MetricValues m){
    std::cout << e << " " << m << std::endl;
    emit IterationPassed(e, m);
    average += m;
  }, do_continue);

  average /= k;

  emit CrossValidationFinished(std::time(nullptr) - start, average);

  if (do_continue != nullptr)
    delete do_continue;
}

void s21::MainModel::LaunchValidation(float alpha, std::size_t iterations) {

  std::time_t start;
  std::time(&start);

  std::size_t end_id = alpha * data_.GetDataSize();
  MetricValues metric;
  for (std::size_t i = 0; i < iterations; i++) {

    data_.ShuffleData();
    auto m = data_.Validate(*perceptron_, 0, end_id);
    metric += m;
    emit IterationPassed(i + 1, m);
  }
  metric /= iterations;

  emit ValidationFinished(std::time(nullptr) - start, metric);
}

void s21::MainModel::ExportPerceptron(QString path) {

  if (path == nullptr)
    return ;

  try {
    perceptron_->ExportPerceptronToFile(path.toStdString(), "");
  }
  catch (...) {
    emit InvalidPath(path);
    return ;
  }
}

void s21::MainModel::StopTraining(bool *controller) {
  *controller = false;
}
