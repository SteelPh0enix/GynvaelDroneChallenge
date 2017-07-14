#ifndef GYNVAELDRONECONTROLLER_HPP
#define GYNVAELDRONECONTROLLER_HPP

#include <QObject>
#include <QString>
#include <QVector>
#include "dronedata.hpp"
#include "dronedatareader.hpp"

class GynvaelDroneController : public QObject {
  Q_OBJECT
  const QString baseFileName{"68eb1a7625837e38d55c54dc99257a17.txt"};
  DroneDataReader dataReader;
  bool firstTime;
  DroneData droneData;

 public:
  explicit GynvaelDroneController(QObject* parent = nullptr);
  bool scanDirection(Direction direction);
  void getFirstData();

 signals:
  void dataReceived(DroneData data);

 public slots:
  void dataReceive(DroneData data);
};

#endif  // GYNVAELDRONECONTROLLER_HPP
