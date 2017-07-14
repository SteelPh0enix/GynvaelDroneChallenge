#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPen>
#include <QPointF>
#include <QColor>
#include <QtMath>
#include <QKeyEvent>
#include <QVector>
#include <QPainter>
#include "gynvaeldronecontroller.hpp"
#include "dronedata.hpp"
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT
  Ui::MainWindow* ui;
  GynvaelDroneController controller;
  QPen dronePen, wallPen;
  QBrush brush;
  QVector<QPointF> walls;
  QPointF drone;

  void start();

 public:
  explicit MainWindow(QWidget* parent = 0);
  ~MainWindow();

 protected:
  void keyPressEvent(QKeyEvent* e);
  void paintEvent(QPaintEvent* event);

 private slots:
  void receivedData(DroneData data);
};

#endif  // MAINWINDOW_HPP
