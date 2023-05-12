#include "s21_main_controller.h"
#include "s21_main_window.h"
#include "s21_main_model.h"
#include "s21_new_perceptron.h"

#include <thread>
#include <iostream>
#include <functional>
#include <QInputDialog>
#include <QMessageBox>

void s21::MainController::SetPerceptronParameters(s21::MainWindow *w, s21::MainModel *m) {

  auto edit = new s21::NewPerceptronWindow(w);

  QObject::connect(edit, &s21::NewPerceptronWindow::ModificationFinished,
                   m, &s21::MainModel::SetPerceptronParameters);

  edit->exec();
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

  bool *do_continue = new bool;
  *do_continue = true;

  QObject::connect(m, &s21::MainModel::IterationPassed,
                   training, &s21::ProgressWindow::ProcessIteration);

  QObject::connect(training, &s21::ProgressWindow::destroyed,
                   w, [&](){
                    *do_continue = false;
                   });

  std::thread myThread([&](){
    m->LaunchTraining(w->GetTrainingEpochs(), do_continue);
  });
  myThread.detach();

  training->exec();
}

void s21::MainController::LaunchCrossValidation(MainWindow *w, MainModel *m) {

  bool ok = false;
  std::size_t k = QInputDialog::getInt(w, "Введите k для кросс-валидации",
                                       "", 10, 1, m->GetDataSize(), 1, &ok);
  if (!ok)
    return ;

  auto validation = new s21::ProgressWindow(w);

  validation->SetIterationsNumber(k);

  bool *do_continue = new bool;
  *do_continue = true;

  QObject::connect(m, &s21::MainModel::IterationPassed,
                   validation, &s21::ProgressWindow::ProcessIteration);

  QObject::connect(validation, &s21::ProgressWindow::destroyed,
                   w, [&](){
                    *do_continue = false;
                   });

  std::thread myThread([&](){
    m->LaunchTraining(w->GetTrainingEpochs(), do_continue);
  });
  myThread.detach();

  validation->exec();
}

void s21::MainController::LaunchValidation(MainWindow *w, MainModel *m) {
  bool ok = false;
  auto alpha = QInputDialog::getDouble(w, "Введите долю набора данных",
                                       "", 1.0, 0.0, 1.0, 2, &ok);
  if (!ok)
    return ;

  auto validation = new s21::ProgressWindow(w);

  validation->SetIterationsNumber(w->GetValidationIterations());

  QObject::connect(m, &s21::MainModel::IterationPassed,
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
