#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

// ---------- WiFi ----------
const char* ssid = "Wokwi-GUEST";
const char* pass = "";

// ---------- MQTT ----------
const char* mqtt_server = "test.mosquitto.org";
const int mqtt_port = 1883;

const char* TOPIC_TEMP = "home/lab1/temp";
const char* TOPIC_HUM  = "home/lab1/hum";

// ---------- DHT ----------
#define DHTPIN 23
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// ---------- MQTT ----------
WiFiClient espClient;
PubSubClient mqtt(espClient);

void connectWiFi() {
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
}

void connectMQTT() {
  while (!mqtt.connected()) {
    String clientId = "ESP32-PUB-";
    clientId += String(random(0xffff), HEX);

    Serial.print("Connecting MQTT...");
    if (mqtt.connect(clientId.c_str())) {
      Serial.println("connected");
    } else {
      Serial.print("failed rc=");
      Serial.println(mqtt.state());
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();

  connectWiFi();
  mqtt.setServer(mqtt_server, mqtt_port);
  connectMQTT();
}

void loop() {
  if (!mqtt.connected()) connectMQTT();
  mqtt.loop();

  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if (!isnan(t) && !isnan(h)) {
    char tBuf[8], hBuf[8];
    dtostrf(t, 4, 2, tBuf);
    dtostrf(h, 4, 2, hBuf);

    mqtt.publish(TOPIC_TEMP, tBuf);
    mqtt.publish(TOPIC_HUM, hBuf);

    Serial.printf("Published -> T:%s  H:%s\n", tBuf, hBuf);
  }

  delay(5000);
}
