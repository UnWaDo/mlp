#include "s21_main_controller.h"
#include "s21_main_window.h"
#include "s21_main_model.h"
#include "s21_draw_image.h"
#include "s21_new_perceptron.h"

#include <thread>
#include <iostream>
#include <functional>
#include <QInputDialog>
#include <QMessageBox>

void s21::MainController::SetPerceptronParameters(s21::MainWindow *w, s21::MainModel *m) {

  auto edit = s21::NewPerceptronWindow(w);

  QObject::connect(&edit, &s21::NewPerceptronWindow::ModificationFinished,
                   m, &s21::MainModel::SetPerceptronParameters);

  edit.exec();
}

void s21::MainController::LoadPerceptron(MainWindow *w, MainModel *m) {
  QString folderPath = QFileDialog::getExistingDirectory(
    w, "Выберите папку", "");
  m->LoadPerceptron(folderPath);
}

void s21::MainController::DrawImage(MainWindow *w, MainModel *m) {

  auto canvas = s21::DrawImageWindow(w);

  QObject::connect(&canvas, &s21::DrawImageWindow::ImageSaved,
                   w, &s21::MainWindow::ImageSelected);
  QObject::connect(&canvas, &s21::DrawImageWindow::ImageSaved,
                   m, &s21::MainModel::PredictImage);

  canvas.exec();
}

void s21::MainController::SelectImage(MainWindow *w, MainModel *m) {
  QString file_path = QFileDialog::getOpenFileName(
      w, "Выберите файл", "", "BMP images (*.bmp)");

  w->ImageSelected(file_path);
  m->PredictImage(file_path);
}

void s21::MainController::LoadData(MainWindow *w, MainModel *m)
{
  QString file_path = QFileDialog::getOpenFileName(
      w, "Выберите файл", "", "All files (*.*)");

  m->LoadData(file_path);
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
  QObject::connect(m, &s21::MainModel::TrainingFinished,
                   training, &s21::ProgressWindow::ProcessIteration);

  QObject::connect(training, &s21::ProgressWindow::rejected,
                   w, [=](){
                    *do_continue = false;
                   });

  std::thread myThread([&, do_continue](){
    m->LaunchTraining(w->GetTrainingEpochs(), do_continue);
    delete do_continue;
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

  QObject::connect(validation, &s21::ProgressWindow::rejected,
                   w, [=](){
                    *do_continue = false;
                   });

  std::thread myThread([&, k, do_continue](){
    m->LaunchCrossValidation(k, w->GetTrainingEpochs(), do_continue);
    delete do_continue;
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

  std::thread myThread([&, alpha](){
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
