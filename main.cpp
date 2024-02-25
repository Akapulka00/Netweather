#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QAuthenticator>
#include <QtNetwork>
#include <QDebug>
#include <QQmlApplicationEngine>
#include "qqmlcontext.h"
#include "weatherdata.h"

QString generateRandomRussianCityName() {
   // Список российских городов
   QStringList russianCityNames = {
       "Москва", "Санкт-Петербург", "Новосибирск", "Екатеринбург", "Нижний Новгород",
        "Казань", "Челябинск", "Омск", "Самара", "Ростов-на-Дону",
       "Уфа", "Красноярск", "Пермь", "Воронеж", "Волгоград",
       "Краснодар", "Саратов", "Тюмень", "Тольятти", "Ижевск",
       // Добавьте больше российских городов по вашему выбору
   };

   int numRussianCities = russianCityNames.size(); // Получаем количество российских городов

   // Генерируем случайный индекс для выбора названия города из списка
   int randomIndex = QRandomGenerator::global()->bounded(numRussianCities);

   return russianCityNames[randomIndex]; // Возвращаем случайно выбранное название города
}


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
   QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
   QGuiApplication app(argc, argv);
   QNetworkAccessManager netMan;

   QNetworkRequest request(QUrl("https://otestserver_1-1-o9142362.deta.app/weather"));
   request.setSslConfiguration(QSslConfiguration::defaultConfiguration()); // Установка SSL-конфигурации

   QNetworkReply* const repl = netMan.get(request);
   QQmlApplicationEngine engine;
     weatherdata *Pogoda = new weatherdata();
   QObject::connect(repl, &QNetworkReply::readyRead, [repl, &engine, &Pogoda]()->void{
      QByteArray data = repl->readAll();
      QJsonDocument jsonResponse = QJsonDocument::fromJson(data);

      if (!jsonResponse.isNull() && jsonResponse.isObject()) {
         QJsonObject jsonObj = jsonResponse.object();

         Pogoda->setWeather(jsonObj["weather"].toArray()[0].toObject()["main"].toString());
         Pogoda->setTemperature(jsonObj["main"].toObject()["temp"].toDouble()-270);
         Pogoda->setPressure(jsonObj["main"].toObject()["pressure"].toInt()-255);
         Pogoda->setHumidity( jsonObj["main"].toObject()["humidity"].toInt());
         Pogoda->setCity(generateRandomRussianCityName());
         if( Pogoda->weather () == "Snow" &&  Pogoda->temperature()>0 )  Pogoda->setTemperature(Pogoda->temperature()*-1);
      //   qDebug()<<"temperature="<< Pogoda.temperature;
     //    qDebug()<<"weatherMain="<< Pogoda.weatherMain;
//qDebug()<<"pressure="<< Pogoda.pressure;
    //      qDebug()<<"City="<< Pogoda.City;
//qDebug()<<"humidity= %"<< Pogoda.humidity;
         // Используйте извлеченные данные по своему усмотрению
      }

   });
    engine.rootContext()->setContextProperty("weatherData", Pogoda);
   const QUrl url(QStringLiteral("qrc:/main.qml"));
   QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
       &app, [url](QObject *obj, const QUrl &objUrl) {
          if (!obj && url == objUrl)
             QCoreApplication::exit(-1);
       }, Qt::QueuedConnection);
   engine.load(url);

   return app.exec();
}
