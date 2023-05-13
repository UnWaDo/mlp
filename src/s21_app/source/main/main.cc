//
// Created by Anton Ivanov on 06.05.2023.
//

#include <QApplication>

#include "s21_main_window.h"

int main(int argc, char** argv) {

  QApplication app(argc, argv);

  s21::MainWindow window;

  window.show();
  return app.exec();
}
