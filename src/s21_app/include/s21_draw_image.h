#ifndef CPP7_MLP_1_SRC_S21_APP_INCLUDE_S21_DRAW_IMAGE_
# define CPP7_MLP_1_SRC_S21_APP_INCLUDE_S21_DRAW_IMAGE_

# include <QApplication>
# include <QWidget>
# include <QRegularExpression>
# include <QPushButton>
# include <QFileDialog>
# include <QLabel>

# include <QMediaPlayer>
# include <QUrl>
# include <QAudioOutput>
# include <QPainter>

namespace s21 {

  class DrawImageWindow : public QDialog {
    Q_OBJECT

    public:
      DrawImageWindow(QWidget *parent = nullptr);
      ~DrawImageWindow();

    public slots:
      void accept() override;

      void mousePressEvent(QMouseEvent* event) override;
      void mouseMoveEvent(QMouseEvent* event) override;

      void paintEvent(QPaintEvent* event) override;

      void SaveImage(QString path);

    signals:
      void ImageSaved(QString path);

    private:
      QLabel display_;
      QImage image_;
      QPainter painter_;
      QPoint last_point_;
  };

}

#endif // CPP7_MLP_1_SRC_S21_APP_INCLUDE_S21_DRAW_IMAGE_
