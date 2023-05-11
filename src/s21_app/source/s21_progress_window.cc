#include <QLineEdit>
#include <QRegularExpressionValidator>
#include <QErrorMessage>

#include "s21_windows.h"
#include "ui_progress_window.h"

s21::ProgressWindow::ProgressWindow(QWidget *parent)
    : QDialog(parent) {

  ui_ = new s21::Ui::ProgressWindow;
  ui_->setupUi(this);

}

s21::ProgressWindow::~ProgressWindow() {
}

void s21::ProgressWindow::SetIterationsNumber(std::size_t i) {

  iterations_ = i;

  ui_->progressBar_->setMaximum(i);
}

void s21::ProgressWindow::ProcessIteration(std::size_t iteration, MetricValues& m) {

  ui_->progressBar_->setValue(iteration);

  QString text;
  QTextStream(&text)  << "Средняя точность: " << m.accuracy << "\n"
                      << "Прецизионность: " << m.precision << "\n"
                      << "Полнота: " << m.recall << "\n"
                      << "F-мера: " << m.f_measure;

  ui_->labelTrainingStatus_->setText(text);

  if (iteration == iterations_)
    emit accept();
}
