#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      controller(this),
      dronePen(Qt::red),
      wallPen(Qt::black),
      brush(Qt::white) {
  ui->setupUi(this);
  QObject::connect(&controller, &GynvaelDroneController::dataReceived, this,
                   &MainWindow::receivedData);

  start();
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::start() {
  controller.scanDirection(Direction::North);
}

void MainWindow::receivedData(DroneData data) {
  drone = (QPointF(data.dronePosition.x(), data.dronePosition.y()));

  QPointF p;

  for (int i{0}; i < data.points.length(); ++i) {
    p = {static_cast<qreal>(data.dronePosition.x()) +
             qSin(qDegreesToRadians(static_cast<double>(i * 10))) *
                 data.points[i],
         static_cast<qreal>(data.dronePosition.y()) -
             qCos(qDegreesToRadians(static_cast<double>(i * 10))) *
                 data.points[i]};
    if (!walls.contains(p))
      walls.append(p);
  }
}

void MainWindow::keyPressEvent(QKeyEvent* e) {
  switch (e->key()) {
    case Qt::Key_Up:
      controller.scanDirection(Direction::North);
      break;
    case Qt::Key_Down:
      controller.scanDirection(Direction::South);
      break;
    case Qt::Key_Right:
      controller.scanDirection(Direction::East);
      break;
    case Qt::Key_Left:
      controller.scanDirection(Direction::West);
      break;
  }
}

void MainWindow::paintEvent(QPaintEvent* event) {
  QMainWindow::paintEvent(event);

  QPainter painter(this);
  painter.setBrush(brush);
  painter.setPen(dronePen);
  painter.setBackground(brush);
  painter.drawPoint(drone);

  painter.setPen(wallPen);
  for (const auto& p : walls)
    painter.drawPoint(p);

  update();
}
