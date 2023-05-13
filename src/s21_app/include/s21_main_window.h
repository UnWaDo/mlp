#ifndef CPP7_MLP_1_SRC_S21_APP_INCLUDE_S21_MAIN_WINDOW_H_
# define CPP7_MLP_1_SRC_S21_APP_INCLUDE_S21_MAIN_WINDOW_H_

# include <QApplication>
# include <QWidget>
# include <QRegularExpression>
# include <QPushButton>
# include <QFileDialog>
# include <QLabel>

# include <QMediaPlayer>
# include <QUrl>
# include <QAudioOutput>

# include "s21_main_model.h"

namespace s21 {
  namespace Ui {
    class MainWindow;
    class ProgressWindow;
  }

  class MainWindow : public QWidget {
    Q_OBJECT

    public:
      MainWindow(QWidget *parent = nullptr);
      ~MainWindow();

      std::size_t GetTrainingEpochs() const;
      std::size_t GetValidationIterations() const;

    public slots:
      void ImageSelected(QString path);
      void ImagePredicted(char c);

      void DataLoaded(QString path, BatchData&);
      void DataCleaned();

      void PerceptronModified(Perceptron::Parameters params, std::string_view type);

      void ValidationFinished(std::time_t t, MetricValues& m);
      void TrainingFinished(std::time_t t, MetricValues& m);
      void CrossValidationFinished(std::time_t t, MetricValues& m);

      void ShowTrainingHistory();

      void InvalidPath(QString path);

    private:
      Ui::MainWindow *ui_;
      QMediaPlayer *player_;
      MainModel *model_;
      QPixmap *image_;
  };

  class ProgressWindow : public QDialog {
    Q_OBJECT

    public:
      ProgressWindow(QWidget *parent = nullptr);
      ~ProgressWindow();

      void SetIterationsNumber(std::size_t i);

    public slots:
      void ProcessIteration(std::size_t epoch, MetricValues&);

    private:
      Ui::ProgressWindow *ui_;
      std::size_t iterations_;
  };

}

#endif // CPP7_MLP_1_SRC_S21_APP_INCLUDE_S21_MAIN_WINDOW_H_