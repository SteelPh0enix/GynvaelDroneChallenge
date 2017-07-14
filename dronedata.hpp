#ifndef DRONEDATA_HPP
#define DRONEDATA_HPP
#include <QVector>
#include <QString>
#include <QStringList>
#include <QPoint>
#include <QMap>

enum class Direction { North = 0, East, South, West };

struct DroneData {
  QPoint dronePosition;
  QVector<double> points;
  QMap<Direction, QString> neightbourFiles;

  DroneData() {}
  DroneData(const QString& rawData) { fromString(rawData); }

  void fromString(const QString& rawData) {
    QStringList splitData = rawData.split('\n');

    {
      QStringList point = splitData[1].split(' ');
      dronePosition = QPoint(point[0].toInt(), point[1].toInt());
    }

    points.resize(36);
    for (int i{0}; i < 36; ++i)
      points[i] = splitData[i + 2].toDouble();

    neightbourFiles[Direction::North] =
        splitData[splitData.length() - 1].split(' ')[1];

    neightbourFiles[Direction::South] =
        splitData[splitData.length() - 2].split(' ')[1];

    neightbourFiles[Direction::West] =
        splitData[splitData.length() - 3].split(' ')[1];

    neightbourFiles[Direction::East] =
        splitData[splitData.length() - 4].split(' ')[1];
  }
};

#endif  // DRONEDATA_HPP
