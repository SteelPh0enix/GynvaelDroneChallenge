#include "drawingarea.hpp"

DrawingArea::DrawingArea(QWidget* parent)
    : QWidget(parent),
      dronePen(Qt::red),
      wallPen(Qt::white),
      backgroundBrush(Qt::black),
      actualPen(&dronePen) {
  setBackgroundRole(QPalette::Base);
  setAutoFillBackground(true);
}

void DrawingArea::paintEvent(QPaintEvent*) {
  QPainter painter(this);
  painter.setPen(*actualPen);
  painter.setBackground(backgroundBrush);
  painter.save();
  painter.drawPoints(points.data(), points.length());
  painter.restore();
}

void DrawingArea::addPoint(const QPointF& point) {
  points.append(point);
  update();
}

QSize DrawingArea::minimumSizeHint() const {
  return QSize(100, 100);
}

QSize DrawingArea::sizeHint() const {
  return QSize(400, 200);
}
