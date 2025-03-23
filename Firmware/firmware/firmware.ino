#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <FastLED.h>

// Аппаратные настройки
#define LED_PIN 5
#define NUM_LEDS 300
#define COLOR_ORDER GRB

// WiFi параметры
const char* SSID = "Crazy Wi-Fi 2.4"; // Используйте только ASCII символы
const char* PASSWORD = "15122004";
const uint16_t SERVER_PORT = 10000;

CRGB leds[NUM_LEDS];
AsyncWebServer server(SERVER_PORT);

// Глобальные переменные для быстрого доступа
const String OK_RESPONSE = "OK";
const String BAD_REQUEST = "Bad Request";

void setupWiFi() {
  WiFi.persistent(false);  // Отключаем сохранение конфигурации WiFi в Flash
  WiFi.mode(WIFI_STA);     // Режим станции
  WiFi.setSleepMode(WIFI_NONE_SLEEP);  // Отключаем спящий режим
  WiFi.begin(SSID, PASSWORD);
  
  while (WiFi.status() != WL_CONNECTED) delay(10);  // Быстрое подключение
}

void setup() {
  // Инициализация светодиодов
  FastLED.addLeds<WS2812B, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS)
    .setCorrection(TypicalLEDStrip)
    .setDither(0);  // Отключаем дитеринг для повышения производительности
  FastLED.setBrightness(50);
  FastLED.clear(true);

  // Настройка WiFi
  setupWiFi();

  // Обработчики запросов
  server.on("/setStripColor", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (request->hasParam("r") && request->hasParam("g") && request->hasParam("b")) {
      // Быстрый парсинг параметров
      const uint8_t r = request->getParam("r")->value().toInt() & 0xFF;
      const uint8_t g = request->getParam("g")->value().toInt() & 0xFF;
      const uint8_t b = request->getParam("b")->value().toInt() & 0xFF;

      // Асинхронное обновление светодиодов
      static bool updateInProgress = false;
      if (!updateInProgress) {
        updateInProgress = true;
        fill_solid(leds, NUM_LEDS, CRGB(r, g, b));
        FastLED.show();
        updateInProgress = false;
      }

      request->send(200, "text/plain", OK_RESPONSE);
    } else {
      request->send(400, "text/plain", BAD_REQUEST);
    }
  });

  server.on("/setLedColors", HTTP_POST, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", OK_RESPONSE);
  }, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
    // Прямая запись в память светодиодов
    if (total == NUM_LEDS * 3) {
      memcpy(leds, data, min(len, sizeof(CRGB) * NUM_LEDS));
      FastLED.show();
    }
  });

  server.begin();
}

void loop() {
  static uint32_t lastCheck = 0;
  if (millis() - lastCheck > 5000) {
    if (WiFi.status() != WL_CONNECTED) {
      WiFi.reconnect();
    }
    lastCheck = millis();
  }
  delay(0);  // Минимальная задержка
}