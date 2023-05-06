//
// Created by Anton Ivanov on 06.05.2023.
//

//#include <QtWidgets/QApplication>
//#include <QtWidgets/QFileDialog>
//#include <iostream>

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QFileDialog>
#include <QLabel>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  // Создаем главное окно
  QWidget window;
  window.setWindowTitle("Выбор папки");
  window.setGeometry(100, 100, 300, 200);

  // Создаем кнопку выбора папки
  QPushButton selectButton("Выбрать папку", &window);
  selectButton.setGeometry(50, 50, 200, 30);

  // Создаем метку для отображения названия папки
  QLabel folderLabel("", &window);
  folderLabel.setGeometry(50, 100, 200, 30);

  // Подключаем сигнал нажатия кнопки к слоту выбора папки
  QObject::connect(&selectButton, &QPushButton::clicked, [&]() {
    QString folderPath = QFileDialog::getExistingDirectory(&window, "Выберите папку", "/");
    folderLabel.setText(folderPath);
  });

  window.show();
  return app.exec();
}
