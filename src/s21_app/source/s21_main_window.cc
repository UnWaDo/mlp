#include "s21_main_window.h"
#include "s21_main_controller.h"
#include "s21_matrix_perceptron.h"
#include "s21_graph_perceptron.h"
#include "s21_training_history.h"
#include "ui_main_window.h"

#include <thread>
#include <iostream>
#include <functional>
#include <QInputDialog>
#include <QMessageBox>

s21::MainWindow::MainWindow(QWidget *parent) : image_(nullptr) {

  ui_ = new s21::Ui::MainWindow;
  ui_->setupUi(this);

  model_ = new s21::MainModel(parent);

  QObject::connect(ui_->draw_image_, &QPushButton::clicked, [&]{
    s21::MainController::DrawImage(this, model_);
  });

  QObject::connect(ui_->select_image_, &QPushButton::clicked, [&]{
    s21::MainController::SelectImage(this, model_);
  });

  QObject::connect(ui_->load_data_, &QPushButton::clicked, [&]{
    s21::MainController::LoadData(this, model_);
  });
  QObject::connect(ui_->clean_data_, &QPushButton::clicked, this, [&]{
    s21::MainController::CleanData(this, model_);
  });

  QObject::connect(ui_->export_perceptron_, &QPushButton::clicked, this, [&]{
    s21::MainController::ExportPerceptron(this, model_);
  });
  QObject::connect(ui_->load_perceptron_, &QPushButton::clicked, this, [&]{
    s21::MainController::LoadPerceptron(this, model_);
  });
  QObject::connect(ui_->new_perceptron_, &QPushButton::clicked, this, [&]{
    s21::MainController::SetPerceptronParameters(this, model_);
  });

  QObject::connect(ui_->start_validation_, &QPushButton::clicked, this, [&]{
    s21::MainController::LaunchValidation(this, model_);
  });
  QObject::connect(ui_->start_training_, &QPushButton::clicked, this, [&]{
    s21::MainController::LaunchTraining(this, model_);
  });
  QObject::connect(ui_->start_cross_validation_, &QPushButton::clicked, this, [&]{
    s21::MainController::LaunchCrossValidation(this, model_);
  });

  QObject::connect(model_, &MainModel::ImagePredicted, this, &MainWindow::ImagePredicted);

  QObject::connect(model_, &MainModel::DataLoaded, this, &MainWindow::DataLoaded);
  QObject::connect(model_, &MainModel::DataCleaned, this, &MainWindow::DataCleaned);

  QObject::connect(model_, &MainModel::PerceptronModified, this, &MainWindow::PerceptronModified);
  QObject::connect(model_, &MainModel::ValidationFinished,
                   this, &MainWindow::ValidationFinished);
  QObject::connect(model_, &MainModel::TrainingFinished,
                   this, &MainWindow::TrainingFinished);
  QObject::connect(model_, &MainModel::CrossValidationFinished,
                   this, &MainWindow::CrossValidationFinished);

  QObject::connect(model_, &MainModel::InvalidPath,
                   this, &MainWindow::InvalidPath);

  QObject::connect(ui_->training_history_, &QPushButton::clicked, this, &MainWindow::ShowTrainingHistory);

  model_->InitializePerceptron();

}

s21::MainWindow::~MainWindow() { }

std::size_t s21::MainWindow::GetTrainingEpochs() const {
  return ui_->training_epochs_->value();
}

std::size_t s21::MainWindow::GetValidationIterations() const {
  return ui_->validation_repeats_->value();
}

void s21::MainWindow::ImageSelected(QString path) {

  ui_->image_holder_->clear();

  if (image_ != nullptr)
    delete image_;

  if (path == nullptr) {
    
    image_ = nullptr;
    return ;
  }

  image_ = new QPixmap(path);
  ui_->image_holder_->setPixmap(*image_);
}


void s21::MainWindow::ImagePredicted(char c) {
  QString text;
  QTextStream(&text) << "На этой картинке буква " << c;
  ui_->image_prediction_->setText(text);
}

void s21::MainWindow::DataLoaded(QString path, BatchData &d)
{

  QString text;
  QTextStream(&text) << "Данные из файла " << path << "\n"
                      << "загружены, всего " << d.GetDataSize() << " строк";

  ui_->data_description_->setText(text);
  ui_->data_description_->setAlignment(Qt::AlignHCenter);
}

void s21::MainWindow::DataCleaned() {
  ui_->data_description_->setText("Данные очищены");
  ui_->data_description_->setAlignment(Qt::AlignHCenter);
}

void s21::MainWindow::PerceptronModified(Perceptron::Parameters params, std::string_view type) {

  QString text;
  auto stream = QTextStream(&text);
  if (type == "Matrix")
    stream << "Матричный перцептрон";
  else
    stream << "Графовый перцептрон";
  stream << "\n" << "Число слоёв: " << params.number_of_layers << "\n";
  stream << "Число нейронов в слоях: " << "\n";
  for (int i = 0; i < params.number_of_layers - 1; i++)
    stream << params.number_of_neurons_in_layer[i] << ", ";
  stream << params.number_of_neurons_in_layer[params.number_of_layers - 1];

  ui_->perceptron_description_->setText(text);

}

void s21::MainWindow::ValidationFinished(std::time_t t, MetricValues &m) {

  QString text;
  QTextStream(&text) << "Валидация заняла " << t << " сек" << "\n"
                     << "Средняя точность: " << m.accuracy << "\n"
                     << "Прецизионность: " << m.precision << "\n"
                     << "Полнота: " << m.recall << "\n"
                     << "F-мера: " << m.f_measure;

  ui_->validation_description_->setText(text);

}

void s21::MainWindow::TrainingFinished(std::time_t t, MetricValues &m) {

  QString text;
  QTextStream(&text) << "Обучение заняло " << t << " сек" << "\n"
                     << "Итоговая точность: " << m.accuracy << "\n"
                     << "Прецизионность: " << m.precision << "\n"
                     << "Полнота: " << m.recall << "\n"
                     << "F-мера: " << m.f_measure;

  ui_->training_description_->setText(text);

}

void s21::MainWindow::CrossValidationFinished(std::time_t t, MetricValues &m) {

  QString text;
  QTextStream(&text) << "Кросс-валидация заняла " << t << " сек" << "\n"
                     << "Средняя точность: " << m.accuracy << "\n"
                     << "Прецизионность: " << m.precision << "\n"
                     << "Полнота: " << m.recall << "\n"
                     << "F-мера: " << m.f_measure;

  ui_->training_description_->setText(text);

}

void s21::MainWindow::ShowTrainingHistory() {

  auto graph = new TrainingHistoryWindow(this);

  graph->ShowTrainingHistory(model_->GetTrainingHistory());
  graph->exec();

}

void s21::MainWindow::InvalidPath(QString path) {

  QMessageBox::warning(this, "Ошибка загрузки", 
                       "Ошибка при загрузке файла " + path);

}
