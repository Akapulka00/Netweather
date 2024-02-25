import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    visible: true
    width: 420
    height: 260
    title: "Weather App"

    Rectangle {
        width: parent.width
        height: parent.height
        color: "white"

        Image {
            id: weatherIcon
            x: 10
            y: 10
            width: 120
            height: 120
            source: ""
            visible: false
        }

        Text {
            id: weatherInfo
            font.family: "Helvetica"
               font.pointSize: 18
            x: weatherIcon.x + weatherIcon.width + 10
            y: weatherIcon.y
            width: parent.width - weatherIcon.width - 30
            wrapMode: Text.Wrap
        }

        Button {
            x: 10
            y: weatherIcon.y + weatherIcon.height + 50
            text: "Получить погоду"
            onClicked: {
                updateWeatherInfo(weatherData);
                weatherIcon.source = getWeatherIcon(weatherData.weather);
                weatherIcon.visible = true;
            }
        }
    }



    function updateWeatherInfo(weatherData) {
        var znak="-";
        var pogoda= weatherData.weather;
        if(pogoda === "Sun"){
        pogoda="Солнечно";
        }else if(pogoda === "Cloudy"){
        pogoda="Облачно";
        }
        else if(pogoda === "Thunderstorm"){
              pogoda="Гроза";
                }
        else if(pogoda === "Rain"){
                pogoda="Дождь";
                }
        else if(pogoda === "Snow"){
                 pogoda="Снег";
                }
        else {
                pogoda="Переменная облачность";
                }
        if(weatherData.temperature >0 ){ znak="+"}
        // Здесь вы можете обновить элементы управления в соответствии с данными о погоде из JSON
        weatherInfo.text = "Город:"+weatherData.city + "\n" +
                           "Температура: " +znak+ Math.abs(weatherData.temperature) + "\n" +
                           "Влажность: %" + weatherData.humidity + "\n" +
                           "Давление: " + weatherData.pressure + "mm \n" +
                           "Погода: " + pogoda;
    }
    function getWeatherIcon(weather) {
        if (weather === "Sun") {
            return "qrc:/Image/Sunny.jpg"; // Путь к изображению для ясной погоды
        } else if (weather === "Cloudy") {
            return "qrc:/Image/Cloudy.jpg"; // Путь к изображению для облачной погоды
        } else if (weather === "Rain") {
            return "qrc:/Image/Rainy.jpg"; // Путь к изображению для дождливой погоды
        } else if (weather === "Thunderstorm"){
            return "qrc:/Image/Thunderstorm.jpg"; // Путь к изображению по умолчанию
        }
        else if (weather === "Snow"){
                    return "qrc:/Image/Snowy.jpg"; // Путь к изображению по умолчанию
                }
        else {
                    return " "; // Путь к изображению по умолчанию
                }
    }
}
