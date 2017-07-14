#ifndef DRAWINGAREA_HPP
#define DRAWINGAREA_HPP

#include <QObject>
#include <QWidget>
#include <QPen>
#include <QColor>
#include <QBrush>
#include <QPainter>
#include <QPaintEvent>
#include <QPoint>
#include <QVector>

class DrawingArea : public QWidget {
  Q_OBJECT
  QPen dronePen, wallPen;
  QBrush backgroundBrush;

  QPen* actualPen;

  QVector<QPointF> points;

 public:
  explicit DrawingArea(QWidget* parent = nullptr);
  void drawWalls(bool f) {
    if (f)
      actualPen = &wallPen;
    else
      actualPen = &dronePen;
  }

  QSize minimumSizeHint() const override;
  QSize sizeHint() const override;

  void addPoint(const QPointF& point);

 protected:
  void paintEvent(QPaintEvent* event) override;

 signals:

 public slots:
};

#endif  // DRAWINGAREA_HPP
