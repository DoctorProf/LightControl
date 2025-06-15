#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_NeoPixel.h>

#define WIFI_SSID "dimanphone"
#define WIFI_PASSWORD "15122004"
#define LED_PIN 0
#define LED_COUNT 300
#define SERVER_PORT 80

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);
AsyncWebServer server(SERVER_PORT);

uint8_t ledBuffer[LED_COUNT * 3];
volatile size_t received = 0;
volatile bool responseSent = false;

void connectToWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  unsigned long startTime = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if (millis() - startTime > 30000) {
      ESP.restart();
    }
  }
}

void setup() {
  Serial.begin(115200);
  connectToWiFi();

  strip.begin();
  strip.setBrightness(50);
  strip.show();

  server.on("/ping", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.print("bobika");
    request->send(200, "text/plain", "esp_ok");
  });
  server.on("/setStripColor", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (!request->hasParam("r") || !request->hasParam("g") || !request->hasParam("b")) {
      request->send(400, "text/plain", "Missing RGB parameters");
      return;
    }

    int r = request->getParam("r")->value().toInt();
    int g = request->getParam("g")->value().toInt();
    int b = request->getParam("b")->value().toInt();

    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
      request->send(400, "text/plain", "Invalid RGB values");
      return;
    }

    for (int i = 0; i < LED_COUNT; i++) {
      strip.setPixelColor(i, strip.Color(r, g, b));
    }
    
    strip.show();
    request->send(200, "text/plain", "OK");
  });

  server.on("/setLedColors", HTTP_POST,
    [](AsyncWebServerRequest *request) {
      received = 0;
      responseSent = false;
    },
    nullptr,
    [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
      if (received + len > sizeof(ledBuffer)) {
        if (!responseSent) {
          request->send(413, "text/plain", "Payload too large");
          responseSent = true;
        }
        return;
      }

      memcpy(ledBuffer + received, data, len);
      received += len;

      if (received == total && !responseSent) {
        if (total != LED_COUNT * 3) {
          request->send(400, "text/plain", "Invalid data length");
          responseSent = true;
          return;
        }

        for (int i = 0; i < LED_COUNT; i++) {
          uint8_t r = ledBuffer[i * 3];
          uint8_t g = ledBuffer[i * 3 + 1];
          uint8_t b = ledBuffer[i * 3 + 2];
          strip.setPixelColor(i, strip.Color(r, g, b));
        }
        
        strip.show();
        request->send(200, "text/plain", "OK");
        responseSent = true;
      }
    });

  server.onNotFound([](AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not Found");
  });

  server.begin();
}

void loop() {
  static unsigned long lastHeapCheck = 0;
  
  if (WiFi.status() != WL_CONNECTED) {
    connectToWiFi();
  }
  
  delay(1);
}