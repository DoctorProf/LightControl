#include <ESP8266WebServer.h>
#include <Adafruit_NeoPixel.h>

// Константы
#define WIFI_SSID "Crazy Wi-Fi 2.4"
#define WIFI_PASSWORD "15122004"
#define LED_PIN      0     // D3 (GPIO0)
#define LED_COUNT    300    // Количество светодиодов
#define SERVER_PORT  80

// Инициализация объектов
ESP8266WebServer server(SERVER_PORT);
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  
  // Подключение к Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected! IP: " + WiFi.localIP().toString());

  // Инициализация ленты
  strip.begin();
  strip.show(); // Очистка ленты

  // Настройка HTTP сервера
  server.on("/setStripColor", HTTP_GET, handleSetStripColor);
  server.on("/setLedColors", HTTP_POST, handleSetLedColors);
  server.onNotFound(handleNotFound);
  
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

// Обработчик установки цвета всей ленты
void handleSetStripColor() {
  if (!server.hasArg("r") || !server.hasArg("g") || !server.hasArg("b")) {
    server.send(400, "text/plain", "Missing RGB parameters");
    return;
  }

  int r = server.arg("r").toInt();
  int g = server.arg("g").toInt();
  int b = server.arg("b").toInt();

  if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
    server.send(400, "text/plain", "Invalid color values (0-255)");
    return;
  }

  // Установка цвета для всех светодиодов
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(r, g, b));
  }
  strip.show();
  
  server.send(200, "text/plain", "OK");
}

// Обработчик установки индивидуальных цветов
void handleSetLedColors() {
  if (server.method() != HTTP_POST) {
    server.send(405, "text/plain", "Method Not Allowed");
    return;
  }

  String body = server.arg("plain");
  if (body.length() != LED_COUNT * 3) {
    server.send(400, "text/plain", 
      "Invalid data length. Expected: " + String(LED_COUNT * 3) + 
      ", received: " + String(body.length()));
    return;
  }

  // Парсинг данных
  for (int i = 0; i < LED_COUNT; i++) {
    int pos = i * 3;
    uint8_t r = body[pos];
    uint8_t g = body[pos + 1];
    uint8_t b = body[pos + 2];
    strip.setPixelColor(i, strip.Color(r, g, b));
  }
  strip.show();
  
  server.send(200, "text/plain", "OK");
}

// Обработчик неизвестных путей
void handleNotFound() {
  server.send(404, "text/plain", "Not Found");
}