#ifndef CPP7_MLP_1_SRC_S21_APP_INCLUDE_S21_WINDOWS_H_
# define CPP7_MLP_1_SRC_S21_APP_INCLUDE_S21_WINDOWS_H_

# include <QApplication>
# include <QWidget>
# include <QPushButton>
# include <QFileDialog>
# include <QLabel>

# include <QMediaPlayer>
# include <QUrl>
# include <QAudioOutput>

# include "s21_batch_data.h"
# include "s21_perceptron.h"

namespace s21 {
  namespace Ui {
    class MainWindow;
  }

  class MainModel : public QObject {
    Q_OBJECT

    public:
      MainModel(QObject *parent = nullptr);
      ~MainModel();

    public slots:
      void SetPerceptronParameters(
        int layers_n,
        std::vector<int>& number_of_neurons,
        float alpha,
        const std::string& activation_name);
      void InitializePerceptron();
      void LoadPerceptron(QString path);
      void LoadData(QString path);
      void CleanData();
      void LaunchTraining();
      void LaunchValidation(float alpha = 1.0);
      void ExportPerceptron(QString path);
    
    signals:
      void DataLoaded(QString path, BatchData&);
      void PerceptronModified(Perceptron::Parameters&, std::string_view type);
      void ValidationFinished(std::time_t, MetricValues&);
      void DataCleaned(BatchData&);

    private:
      Perceptron::Parameters perceptron_params_;
      std::string perceptron_type_;
      Perceptron *perceptron_;
      BatchData data_;
  };

  class MainWindow : public QWidget {
    Q_OBJECT

    public:
      MainWindow(QWidget *parent = nullptr);
      ~MainWindow();

    private:
      Ui::MainWindow *ui;
      QMediaPlayer *player_;
      MainModel *model_;
  };

  // class SetupWindow : public QWidget {
  //   Q_OBJECT

  //   public:
  //     SetupWindow(QWidget *parent = nullptr);
  //     ~SetupWindow();

  //   signals:
  //     void SetPerceptronParameters(
  //       int layers_n,
  //       std::vector<int>& number_of_neurons,
  //       float alpha,
  //       const std::string& activation_name);
  // };

  class MainController {
    public:
      static void SetPerceptronParameters(MainWindow *, MainModel *);
      static void InitializePerceptron(MainWindow *, MainModel *);
      static void LoadPerceptron(MainWindow *, MainModel *);
      static void LoadData(MainWindow *, MainModel *);
      static void CleanData(MainWindow *, MainModel *);
      static void LaunchTraining(MainWindow *, MainModel *);
      static void LaunchValidation(MainWindow *, MainModel *);
      static void ExportPerceptron(MainWindow *, MainModel *);
  };

}

#endif // CPP7_MLP_1_SRC_S21_APP_INCLUDE_S21_WINDOWS_H_