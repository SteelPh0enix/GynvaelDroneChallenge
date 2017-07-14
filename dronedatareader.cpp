#include "dronedatareader.hpp"

DroneDataReader::DroneDataReader(QObject* parent)
    : QObject(parent), manager(this) {
  if (!QDir("buffer").exists())
    QDir().mkdir("buffer");

  QObject::connect(&manager, &QNetworkAccessManager::finished, this,
                   &DroneDataReader::dataReaded);
}

bool DroneDataReader::getData(const QString& filename) {
  if (filename == "not")
    return false;
  try {
    getBufferedData("buffer\\" + filename);
  } catch (...) {
    try {
      getRemoteData(filename);
    } catch (...) {
      return false;
    }
  }

  return true;
}

void DroneDataReader::getBufferedData(const QString& filename) {
  QFile file(filename);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    throw std::logic_error("Can't find buffered file!");

  QTextStream in(&file);
  emit dataPrepared(DroneData(in.readAll()));
}

void DroneDataReader::getRemoteData(const QString& filename) {
  try {
    manager.get(QNetworkRequest(QUrl(baseAddress + filename)));
  } catch (const std::exception& e) {
    throw e;
  }
}

void DroneDataReader::dataReaded(QNetworkReply* reply) {
  auto data = QString(reply->readAll());
  QFile buf("buffer\\" + reply->url().toString().split('/')[5]);
  if (buf.open(QIODevice::WriteOnly | QIODevice::Text)) {
    buf.write(QByteArray(data.toUtf8()));
    buf.close();
  }

  emit dataPrepared(DroneData(data));
}
