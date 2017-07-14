#ifndef DRONEDATAREADER_HPP
#define DRONEDATAREADER_HPP

#include <QObject>
#include <QString>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <exception>
#include "dronedata.hpp"

class DroneDataReader : public QObject {
  Q_OBJECT
  const QString baseAddress{
      "http://gynvael.coldwind.pl/misja008_drone_io/scans/"};
  QString dataBuffer;
  QNetworkAccessManager manager;

  void getBufferedData(const QString& filename);
  void getRemoteData(const QString& filename);

 public:
  explicit DroneDataReader(QObject* parent = nullptr);
  bool getData(const QString& filename);

 signals:
  void dataPrepared(DroneData dataBuffer);

 private slots:
  void dataReaded(QNetworkReply* reply);
};

#endif  // DRONEDATAREADER_HPP
