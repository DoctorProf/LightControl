#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Настройки Wi-Fi
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// Создание объекта веб-сервера на порту 80
ESP8266WebServer server(80);

void handleRoot() {
  // Получение текущего времени
  unsigned long currentTime = millis() / 1000;

  // Формирование HTML страницы
  String html = "<!DOCTYPE html><html><body><h1>Current Time</h1><p>";
  html += currentTime;
  html += " seconds</p></body></html>";

  // Отправка HTML страницы клиенту
  server.send(200, "text/html", html);
}

void setup() {
  // Инициализация последовательного порта для отладки
  Serial.begin(115200);

  // Подключение к Wi-Fi сети
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Отображение IP-адреса
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Настройка обработчика для корневого URL
  server.on("/", handleRoot);

  // Запуск веб-сервера
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Обработка входящих HTTP-запросов
  server.handleClient();
}
