#include "gynvaeldronecontroller.hpp"

GynvaelDroneController::GynvaelDroneController(QObject* parent)
    : QObject(parent), dataReader(this), firstTime(true) {
  QObject::connect(&dataReader, &DroneDataReader::dataPrepared, this,
                   &GynvaelDroneController::dataReceive);
}

void GynvaelDroneController::dataReceive(DroneData data) {
  droneData = data;
  emit dataReceived(data);
}

void GynvaelDroneController::getFirstData() {
  dataReader.getData(baseFileName);
}

bool GynvaelDroneController::scanDirection(Direction direction) {
  if (firstTime) {
    getFirstData();
    firstTime = false;
    return true;
  } else {
    return dataReader.getData(droneData.neightbourFiles[direction]);
  }
}
