#ifndef CPP7_MLP_1_SRC_S21_APP_INCLUDE_S21_TRAINING_HISTORY_
# define CPP7_MLP_1_SRC_S21_APP_INCLUDE_S21_TRAINING_HISTORY_

# include <QApplication>
# include <QWidget>
# include "qcustomplot.h"
# include "s21_batch_data.h"

namespace s21 {

  class TrainingHistoryWindow : public QDialog {
    Q_OBJECT

    public:
      TrainingHistoryWindow(QWidget *parent = nullptr);
      ~TrainingHistoryWindow();

    public slots:
      void ShowTrainingHistory(const std::vector<MetricValues>& data);

    private:
      QCustomPlot* plot_;

  };

}

#endif // CPP7_MLP_1_SRC_S21_APP_INCLUDE_S21_TRAINING_HISTORY_