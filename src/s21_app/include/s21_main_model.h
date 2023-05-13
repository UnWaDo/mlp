#ifndef CPP7_MLP_1_SRC_S21_APP_INCLUDE_S21_MAIN_MODEL_H_
# define CPP7_MLP_1_SRC_S21_APP_INCLUDE_S21_MAIN_MODEL_H_

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

  class MainModel : public QObject {
    Q_OBJECT

    public:
      MainModel(QObject *parent = nullptr);
      ~MainModel();

      std::size_t GetDataSize() const;

    public slots:
      void PredictImage(QString path);

      void LoadData(QString path);
      void CleanData();
      void SetPerceptronParameters(Perceptron::Parameters& params,
                                   std::string_view type);
      void InitializePerceptron();
      void LoadPerceptron(QString path);
      void ExportPerceptron(QString path);
      void LaunchValidation(float alpha = 1.0, std::size_t iterations = 1);
      void LaunchTraining(std::size_t epochs = 100, bool *do_continue = nullptr);
      void LaunchCrossValidation(std::size_t k, std::size_t epochs = 100,
                                 bool *do_continue = nullptr);
      void StopTraining(bool *controller);
    
    signals:
      void ImagePredicted(char c);

      void DataLoaded(QString path, BatchData&);
      void DataCleaned();

      void PerceptronModified(Perceptron::Parameters&, std::string_view type);

      void IterationPassed(std::size_t i, MetricValues&);

      void TrainingFinished(std::time_t, MetricValues&);
      void ValidationFinished(std::time_t, MetricValues&);
      void CrossValidationFinished(std::time_t, MetricValues&);

      void InvalidPath(QString path);

    private:
      Perceptron::Parameters perceptron_params_;
      std::string perceptron_type_;
      Perceptron *perceptron_;
      BatchData data_;
  };

}

#endif // CPP7_MLP_1_SRC_S21_APP_INCLUDE_S21_MAIN_MODEL_H_