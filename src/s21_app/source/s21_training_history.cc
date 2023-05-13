#include "s21_training_history.h"

s21::TrainingHistoryWindow::TrainingHistoryWindow(QWidget *parent) : QDialog(parent) {

  plot_ = new QCustomPlot(this);
  plot_->setGeometry(0, 0, 300, 200);
  plot_->addGraph();
}

s21::TrainingHistoryWindow::~TrainingHistoryWindow() {
}

void s21::TrainingHistoryWindow::ShowTrainingHistory(const std::vector<s21::MetricValues>& history) {

  QVector<double> epochs(history.size());
  QVector<double> f_measure(history.size());

  for (std::size_t i = 0; i < history.size(); i++) {

    epochs.append(i);
    f_measure.append(history[i].f_measure);
  }

  plot_->graph(0)->setData(epochs, f_measure);
  plot_->replot();
  plot_->graph(0)->rescaleAxes();
}