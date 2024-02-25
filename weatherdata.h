#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <QObject>

class weatherdata : public QObject
{
   Q_OBJECT
   public:
   explicit weatherdata(QObject *parent = nullptr);
       Q_PROPERTY(double temperature READ temperature WRITE setTemperature NOTIFY temperatureChanged)
       Q_PROPERTY(int pressure READ pressure WRITE setPressure NOTIFY pressureChanged)
       Q_PROPERTY(int humidity READ humidity WRITE setHumidity NOTIFY humidityChanged)
       Q_PROPERTY(QString city READ city WRITE setCity NOTIFY cityChanged)
        Q_PROPERTY(QString weather READ weather WRITE setWeather NOTIFY weatherChanged)

       double m_temperature;
       int m_pressure;
       int m_humidity;
       QString m_city;
       QString m_weather;

       double temperature() const { return m_temperature; }
       int pressure() const { return m_pressure; }
       int humidity() const { return m_humidity; }
       QString city() const { return m_city; }
      QString weather () const { return m_weather; }

   public slots:
       void setTemperature(double temperature) {
          if (m_temperature != temperature) {
             m_temperature = temperature;
             emit temperatureChanged();
          }
       }
       void setPressure(int pressure) {
          if (m_pressure != pressure) {
             m_pressure = pressure;
             emit pressureChanged();
          }
       }
       void setHumidity(int humidity) {
          if (m_humidity != humidity) {
             m_humidity = humidity;
             emit humidityChanged();
          }
       }
       void setCity(const QString &city) {
          if (m_city != city) {
             m_city = city;
             emit cityChanged();
          }
       }
       void setWeather(const QString &weather) {
          if (m_weather != weather) {
             m_weather = weather;
             emit weatherChanged();
          }
       }

   signals:
       void temperatureChanged();
       void pressureChanged();
       void humidityChanged();
       void cityChanged();
       void weatherChanged();


};

#endif // WEATHERDATA_H
