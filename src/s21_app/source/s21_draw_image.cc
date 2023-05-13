#include <QPainter>
#include <iostream>
#include "s21_draw_image.h"
#include <QMouseEvent>

s21::DrawImageWindow::DrawImageWindow(QWidget* parent)
    : QDialog(parent)
    , display_(parent)
    , image_(512, 512, QImage::Format_RGB16)
    , painter_(&image_) {

  image_.fill(qRgb(0xFF, 0xFF, 0xFF));

  painter_.setPen(
      QPen(Qt::black, 18, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  painter_.setRenderHint(QPainter::SmoothPixmapTransform);
  painter_.setRenderHint(QPainter::Antialiasing);

  display_.setPixmap(QPixmap::fromImage(image_));
  display_.setGeometry(0, 0, 512, 512);

  auto submit = new QPushButton(this);
  submit->setGeometry(0, 530, 512, 20);
  submit->setText("Сохранить изображение");

  QObject::connect(submit, &QPushButton::clicked, [&]{

    QString folderPath = QFileDialog::getSaveFileName(
      this, "Сохранить как...", "", "BMP images (*.bmp)");

    this->SaveImage(folderPath);
  });

  update();
}

s21::DrawImageWindow::~DrawImageWindow() {}

void s21::DrawImageWindow::accept() {}

void s21::DrawImageWindow::mousePressEvent(QMouseEvent* event) {
  last_point_ = event->pos();
}

void s21::DrawImageWindow::mouseMoveEvent(QMouseEvent* event) {

  auto point = event->pos();
  painter_.drawLine(last_point_, point);

  last_point_ = event->pos();
  display_.setPixmap(QPixmap::fromImage(image_));

  int rad = 12;
  update(
    QRect(last_point_, point).normalized().adjusted(-rad, -rad, +rad, +rad));
}

void s21::DrawImageWindow::paintEvent(QPaintEvent* event) {

  QPainter painter(this);
  QRect rect(event->rect());
  painter.drawImage(rect, image_, rect);
}

void s21::DrawImageWindow::SaveImage(QString path) {

  if (path == nullptr)
    return ;

  if (!path.endsWith(".bmp"))
    path += ".bmp";

  image_.save(path);
  // auto pixmap = QPixmap::fromImage(image_);
  // pixmap.save(path);
}

