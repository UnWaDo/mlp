#ifndef CPP7_MLP_1_SRC_S21_APP_INCLUDE_S21_WINDOWS_H_
# define CPP7_MLP_1_SRC_S21_APP_INCLUDE_S21_WINDOWS_H_

# include <QApplication>
# include <QWidget>
# include <QRegularExpression>
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
    class EditPerceptronWindow;
    class ProgressWindow;
  }

  class MainModel : public QObject {
    Q_OBJECT

    public:
      MainModel(QObject *parent = nullptr);
      ~MainModel();

    public slots:
      void SetPerceptronParameters(Perceptron::Parameters& params,
                                   std::string_view type);
      void InitializePerceptron();
      void LoadPerceptron(QString path);
      void LoadData(QString path);
      void CleanData();
      void LaunchTraining(std::size_t epochs = 100);
      void LaunchValidation(float alpha = 1.0, std::size_t iterations = 1);
      void ExportPerceptron(QString path);
    
    signals:
      void DataLoaded(QString path, BatchData&);
      void PerceptronModified(Perceptron::Parameters&, std::string_view type);
      void ValidationFinished(std::time_t, MetricValues&);
      void DataCleaned(BatchData&);
      void TrainingIteration(std::size_t epoch, MetricValues&);

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

      std::size_t GetTrainingEpochs() const;
      std::size_t GetValidationIterations() const;

    private:
      Ui::MainWindow *ui_;
      QMediaPlayer *player_;
      MainModel *model_;
  };

  class EditPerceptronWindow : public QDialog {
    Q_OBJECT

    public:
      EditPerceptronWindow(QWidget *parent = nullptr);
      ~EditPerceptronWindow();

    public slots:
      void accept() override;

    signals:
      void ModificationFinished(
          Perceptron::Parameters&,
          std::string_view perceptron_type);

    private:
      Ui::EditPerceptronWindow *ui_;
      QRegularExpression re_field_;
      QRegularExpression re_token_;
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