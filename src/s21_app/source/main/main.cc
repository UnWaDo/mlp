//
// Created by Anton Ivanov on 06.05.2023.
//

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QFileDialog>
#include <QLabel>
#include <iostream>

#include "s21_batch_data.h"
#include "s21_matrix_perceptron.h"


#include <thread>


#include <QMediaPlayer>
#include <QUrl>
#include <QAudioOutput>

QMediaPlayer* player;
MatrixPerceptron* perceptron;
s21::BatchData* data;

void Train() {

  std::cout << "Старт" << std::endl;
  auto metric = data->Validate(*perceptron);
  std::cout << metric << std::endl;
  data->SetMaxSteps(100);
  std::cout << "Учусь" << std::endl;
  data->Train(*perceptron);
  std::cout << "Готово" << std::endl;
  metric = data->Validate(*perceptron);
  std::cout << metric << std::endl;

  player->play();
}

int main(int argc, char** argv) {





  QApplication app(argc, argv);


  player = new QMediaPlayer;
  auto audioOutput = new QAudioOutput;
  player->setAudioOutput(audioOutput);

  player->setSource(QUrl::fromLocalFile("/Users/ivnvtosh/Desktop/done.m4a"));
  audioOutput->setVolume(50);


  data = new s21::BatchData(26, 784);
  auto parameters = s21::Perceptron::Parameters();

  parameters.number_of_layers = 5;
//  parameters.number_of_neurons_in_layer = new int[5]{784, 1568, 1000, 78, 26};
  parameters.number_of_neurons_in_layer = new int[5]{784, 20, 20, 20, 26};
  parameters.activation_name = "Sigmoid";
  parameters.alpha = 0.05f;

  perceptron = new MatrixPerceptron(parameters);

  // Создаем главное окно
  QWidget window;

  window.setWindowTitle("Нейронка");
  window.setGeometry(100, 100, 300, 400);

  QPushButton selectDataset("Выбрать набор данных", &window);
  selectDataset.setGeometry(50, 50, 200, 30);

  QPushButton selectLaunch("Запуск", &window);
  selectLaunch.setGeometry(50, 110, 200, 30);

//  QLabel folderLabel("", &window);
//  folderLabel.setGeometry(50, 100, 200, 30);

  QPushButton saveWeights("Сохранить веса", &window);
  saveWeights.setGeometry(50, 210, 200, 30);

  // Подключаем сигнал нажатия кнопки к слоту выбора папки
  QObject::connect(&selectDataset, &QPushButton::clicked, [&]() {
    QString filePath = QFileDialog::getOpenFileName(nullptr, "Выберите файл", "", "All files (*.*)");

    data->LoadData(filePath.toStdString());
  });

  QObject::connect(&selectLaunch, &QPushButton::clicked, [&]() {
//    QString folderPath = QFileDialog::getExistingDirectory(&window, "Запуск", "/");

    std::thread myThread(Train);
    myThread.detach();
  });

  QObject::connect(&saveWeights, &QPushButton::clicked, [&]() {
//    QString folderPath = QFileDialog::getExistingDirectory(&window, "Выберите папку", "/");

    perceptron->ExportPerceptronToFile("дитя");
  });

  window.show();
  return app.exec();
}
