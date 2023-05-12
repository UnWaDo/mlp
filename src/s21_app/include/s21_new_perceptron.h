#ifndef CPP7_MLP_1_SRC_S21_APP_INCLUDE_S21_NEW_PERCEPTRON_H_
# define CPP7_MLP_1_SRC_S21_APP_INCLUDE_S21_NEW_PERCEPTRON_H_

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
    class NewPerceptronWindow;
  }

  class NewPerceptronWindow : public QDialog {
    Q_OBJECT

    public:
      NewPerceptronWindow(QWidget *parent = nullptr);
      ~NewPerceptronWindow();

    public slots:
      void accept() override;

    signals:
      void ModificationFinished(
          Perceptron::Parameters&,
          std::string_view perceptron_type);

    private:
      Ui::NewPerceptronWindow *ui_;
      QRegularExpression re_field_;
      QRegularExpression re_token_;
  };


}

#endif // CPP7_MLP_1_SRC_S21_APP_INCLUDE_S21_NEW_PERCEPTRON_H_