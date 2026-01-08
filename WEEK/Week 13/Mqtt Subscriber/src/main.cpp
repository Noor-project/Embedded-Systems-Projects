#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ---------- WiFi ----------
const char* ssid = "Wokwi-GUEST";
const char* pass = "";

// ---------- MQTT ----------
const char* mqtt_server = "test.mosquitto.org";
const int mqtt_port = 1883;

const char* TOPIC_TEMP = "home/lab1/temp";
const char* TOPIC_HUM  = "home/lab1/hum";

// ---------- OLED ----------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ---------- MQTT ----------
WiFiClient espClient;
PubSubClient mqtt(espClient);
String lastTemp = "--";
String lastHum  = "--";

// ---------- Display function ----------
void showData() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("MQTT Monitor");
  display.println("----------------");

  display.setTextSize(2);
  display.setCursor(0, 20);
  display.print("Temp: ");
  display.print(lastTemp);
  display.println(" C");

  display.setCursor(0, 45);
  display.print("Hum:  ");
  display.print(lastHum);
  display.println(" %");

  display.display();
}

// ---------- MQTT callback ----------
void callback(char* topic, byte* payload, unsigned int length) {
  String msg;
  for (unsigned int i = 0; i < length; i++) msg += (char)payload[i];
  msg.trim();

  if (String(topic) == TOPIC_TEMP) {
    lastTemp = msg;
    Serial.print("Received Temp: ");
    Serial.println(lastTemp);
  } else if (String(topic) == TOPIC_HUM) {
    lastHum = msg;
    Serial.print("Received Humidity: ");
    Serial.println(lastHum);
  }
  showData();
}

// ---------- WiFi connection ----------
void connectWiFi() {
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
}

// ---------- MQTT connection ----------
void connectMQTT() {
  while (!mqtt.connected()) {
    String clientId = "ESP32-SUB-";
    clientId += String(random(0xffff), HEX);

    Serial.print("Connecting MQTT...");
    if (mqtt.connect(clientId.c_str())) {
      Serial.println("connected");
      mqtt.subscribe(TOPIC_TEMP);
      mqtt.subscribe(TOPIC_HUM);
      showData();
    } else {
      Serial.print("failed rc=");
      Serial.println(mqtt.state());
      delay(2000);
    }
  }
}

// ---------- Setup ----------
void setup() {
  Serial.begin(115200);

  Wire.begin(21, 22);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();

  connectWiFi();
  mqtt.setServer(mqtt_server, mqtt_port);
  mqtt.setCallback(callback);
  connectMQTT();
}

// ---------- Loop ----------
void loop() {
  if (!mqtt.connected()) connectMQTT();
  mqtt.loop();
}
