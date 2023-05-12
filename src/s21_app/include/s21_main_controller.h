#ifndef CPP7_MLP_1_SRC_S21_APP_INCLUDE_S21_MAIN_CONTROLLER_H_
# define CPP7_MLP_1_SRC_S21_APP_INCLUDE_S21_MAIN_CONTROLLER_H_

# include <QApplication>
# include <QWidget>
# include <QRegularExpression>
# include <QPushButton>
# include <QFileDialog>
# include <QLabel>

# include <QMediaPlayer>
# include <QUrl>
# include <QAudioOutput>

# include "s21_main_window.h"
# include "s21_main_model.h"

namespace s21 {

  class MainController {
    public:
      static void LoadData(MainWindow *, MainModel *);
      static void CleanData(MainWindow *, MainModel *);

      static void SetPerceptronParameters(MainWindow *, MainModel *);
      static void LoadPerceptron(MainWindow *, MainModel *);
      static void ExportPerceptron(MainWindow *, MainModel *);

      static void LaunchValidation(MainWindow *, MainModel *);
      static void LaunchTraining(MainWindow *, MainModel *);
      static void LaunchCrossValidation(MainWindow *, MainModel *);
  };

}

#endif // CPP7_MLP_1_SRC_S21_APP_INCLUDE_S21_MAIN_CONTROLLER_H_
