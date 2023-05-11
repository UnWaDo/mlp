#include "s21_windows.h"
#include "s21_matrix_perceptron.h"
#include "s21_graph_perceptron.h"
#include "ui_main_window.h"

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

  Perceptron *new_perceptron;

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

  if (path == nullptr) {
    // emit PerceptronLoadingFailed(path);
    return ;
  }
  try {
    if (perceptron_type_ == "Matrix")
      new_perceptron = new MatrixPerceptron(path.toStdString());
    else
      new_perceptron = new GraphPerceptron(path.toStdString());
  }
  catch (...) {
    // emit PerceptronLoadingFailed(path);
    return ;
  }
  delete perceptron_;
  perceptron_ = new_perceptron;

  emit PerceptronModified(perceptron_params_, perceptron_type_);
  // emit PerceptronReloaded(perceptron_);
}

void s21::MainModel::LoadData(QString path)
{

  if (path == nullptr) {
    // emit DataLoadingFailed(path);
    return ;
  }

  try {
    data_.LoadData(path.toStdString());
    // emit DataLoaded(data_);
  }
  catch (...) {
    // emit DataLoadingFailed(path);
    return ;
  }
  emit DataLoaded(path, data_);
}

void s21::MainModel::CleanData() {
  data_.PurgeData();
  emit DataCleaned(data_);
}

void s21::MainModel::LaunchTraining(std::size_t epochs)
{

  std::cout << "Старт" << std::endl;

  auto metric = data_.Validate(*perceptron_);
  std::cout << metric << std::endl;

  data_.SetMaxSteps(epochs);

  std::cout << "Учусь" << std::endl;

  data_.Train(*perceptron_, [&](std::size_t e, s21::MetricValues m){
    std::cout << e << " " << m << std::endl;
    emit TrainingIteration(e, m);
  });
  std::cout << "Готово" << std::endl;

  metric = data_.Validate(*perceptron_);
  std::cout << metric << std::endl;
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
    emit TrainingIteration(i + 1, m);
  }
  metric /= iterations;

  emit ValidationFinished(std::time(nullptr) - start, metric);
}

void s21::MainModel::ExportPerceptron(QString path) {

  if (path == nullptr) {
    std::cout << "Extra lol" << std::endl;
    return ;
  }
  try {
    perceptron_->ExportPerceptronToFile(path.toStdString(), "");
  }
  catch (...) {
    std::cout << "LOL" << std::endl;
    return ;
  }
  // emit PerceptronExported(path);
}

s21::MainWindow::MainWindow(QWidget *parent) {

  auto font = this->font();
  font.setPointSize(16);
  this->setFont(font);

  ui_ = new s21::Ui::MainWindow;
  ui_->setupUi(this);

  model_ = new s21::MainModel(parent);

  player_ = new QMediaPlayer;
  auto audioOutput = new QAudioOutput;
  player_->setAudioOutput(audioOutput);

  player_->setSource(QUrl::fromLocalFile("/Users/ivnvtosh/Desktop/done.m4a"));
  audioOutput->setVolume(50);

  QObject::connect(ui_->ButtonLoadData, &QPushButton::clicked, [&]{
    s21::MainController::LoadData(this, model_);
  });

  QObject::connect(ui_->ButtonStartTraining, &QPushButton::clicked, this, [&]{
    s21::MainController::LaunchTraining(this, model_);
  });

  QObject::connect(ui_->ButtonExportParameters, &QPushButton::clicked, this, [&]{
    s21::MainController::ExportPerceptron(this, model_);
  });

  QObject::connect(ui_->ButtonImportParameters, &QPushButton::clicked, this, [&]{
    s21::MainController::LoadPerceptron(this, model_);
  });

  QObject::connect(ui_->ButtonChangeParameters, &QPushButton::clicked, this, [&]{
    s21::MainController::SetPerceptronParameters(this, model_);
  });

  QObject::connect(ui_->ButtonStartValidation, &QPushButton::clicked, this, [&]{
    s21::MainController::LaunchValidation(this, model_);
  });

  QObject::connect(ui_->ButtonCleanData, &QPushButton::clicked, this, [&]{
    s21::MainController::CleanData(this, model_);
  });

  QObject::connect(model_, &MainModel::DataLoaded, [=](QString p, BatchData& d){
    QString text;
    QTextStream(&text) << "Данные из файла " << p << "\n"
                       << "загружены, всего " << d.GetDataSize() << " строк";
    ui_->LabelDataDescription->setText(text);
  });

  QObject::connect(model_, &MainModel::DataCleaned, [=](BatchData& d){
    (void) d;
    ui_->LabelDataDescription->setText("Данные очищены");
  });

  QObject::connect(model_, &MainModel::PerceptronModified,
                  [&](Perceptron::Parameters params, std::string_view type){
    QString text;
    auto stream = QTextStream(&text);
    if (type == "Matrix")
      stream << "Матричный перцептрон";
    else
      stream << "Графовый перцептрон";
    stream << "\n" << "Число слоёв: " << params.number_of_layers << "\n";
    stream << "Число нейронов в слоях: ";
    for (int i = 0; i < params.number_of_layers - 1; i++)
      stream << params.number_of_neurons_in_layer[i] << ", ";
    stream << params.number_of_neurons_in_layer[params.number_of_layers - 1];
    ui_->LabelPerceptronDescription->setText(text);
  });

  model_->InitializePerceptron();

  QObject::connect(model_, &MainModel::ValidationFinished, [=](std::time_t t, MetricValues& m){
    QString text;
    QTextStream(&text) << "Валидация заняла " << t << " сек" << "\n"
                       << "Средняя точность: " << m.accuracy << "\n"
                       << "Прецизионность: " << m.precision << "\n"
                       << "Полнота: " << m.recall << "\n"
                       << "F-мера: " << m.f_measure;
    ui_->LabelValidationDescription->setText(text);
  });
}

s21::MainWindow::~MainWindow() { }

std::size_t s21::MainWindow::GetTrainingEpochs() const {
  return ui_->SpinBoxTrainingEpochs->value();
}

std::size_t s21::MainWindow::GetValidationIterations() const {
  return ui_->SpinBoxValidationRepeats->value();
}

void s21::MainController::SetPerceptronParameters(s21::MainWindow *w, s21::MainModel *m) {

  auto edit = new s21::EditPerceptronWindow(w);

  QObject::connect(edit, &s21::EditPerceptronWindow::ModificationFinished,
                   m, &s21::MainModel::SetPerceptronParameters);

  edit->exec();
}

void s21::MainController::InitializePerceptron(MainWindow *w, MainModel *m) {
  (void) w;
  (void) m;
}

void s21::MainController::LoadPerceptron(MainWindow *w, MainModel *m) {
  QString folderPath = QFileDialog::getExistingDirectory(
    w, "Выберите папку", "");
  m->LoadPerceptron(folderPath);
}

void s21::MainController::LoadData(MainWindow *w, MainModel *m) {
  QString filePath = QFileDialog::getOpenFileName(
      w, "Выберите файл", "", "All files (*.*)");

  m->LoadData(filePath);
}

void s21::MainController::CleanData(MainWindow *w, MainModel *m) {
  QMessageBox message_box(w);
  message_box.setText("Подтвердите очистку данных");
  message_box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
  message_box.setDefaultButton(QMessageBox::Cancel);
  auto action = message_box.exec();
  if (action == QMessageBox::Ok)
    m->CleanData();
}

void s21::MainController::LaunchTraining(MainWindow *w, MainModel *m) {

  auto training = new s21::ProgressWindow(w);

  training->SetIterationsNumber(w->GetTrainingEpochs());

  QObject::connect(m, &s21::MainModel::TrainingIteration,
                   training, &s21::ProgressWindow::ProcessIteration);

  std::thread myThread([&](){
    m->LaunchTraining(w->GetTrainingEpochs());
  });
  myThread.detach();

  training->exec();
}

void s21::MainController::LaunchValidation(MainWindow *w, MainModel *m) {
  bool ok = false;
  auto alpha = QInputDialog::getDouble(w, "Введите долю набора данных",
                                       "", 1.0, 0.0, 1.0, 2, &ok);
  if (!ok)
    return ;

  auto validation = new s21::ProgressWindow(w);

  validation->SetIterationsNumber(w->GetValidationIterations());

  QObject::connect(m, &s21::MainModel::TrainingIteration,
                   validation, &s21::ProgressWindow::ProcessIteration);

  std::thread myThread([&](){
    m->LaunchValidation(alpha, w->GetValidationIterations());
  });
  myThread.detach();

  validation->exec();
}

void s21::MainController::ExportPerceptron(MainWindow *w, MainModel *m) {
  QString folderPath = QFileDialog::getSaveFileName(
    w, "Выберите папку", "");
  m->ExportPerceptron(folderPath);
}
