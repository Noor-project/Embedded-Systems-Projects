/************ BLYNK CONFIG ************/
#define BLYNK_TEMPLATE_ID "TMPL6tw9qk6Yy"
#define BLYNK_TEMPLATE_NAME "Water Quality Monitoring System"
#define BLYNK_AUTH_TOKEN "4fTzgLOK1Rp2t1TqcbiBb0iF3MriJPEN"

#define BLYNK_PRINT Serial
#define BLYNK_SERVER "blynk.cloud"
#define BLYNK_PORT 80

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <ThingSpeak.h>

// ================= WIFI =================
const char* ssid = "Numan 5G Home";
const char* password = "11680116";

// ================= THINGSPEAK =================
unsigned long channelID = 3214366;
const char* writeAPIKey = "1DP1DPU5359IIFLE";
WiFiClient client;
unsigned long lastUpload = 0;
#define UPLOAD_INTERVAL 15000

// -------------------- PIN CONFIG --------------------
#define TURBIDITY_PIN 34
#define TDS_PIN 35
#define BUZZER_PIN 25

// -------------------- OLED --------------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// -------------------- TDS CALIBRATION --------------------
#define VREF 3.3

// -------------------- TIMING --------------------
#define LIVE_DURATION 5000
#define LOCKED_DURATION 10000

// -------------------- AVERAGING --------------------
#define AVG_SAMPLES 10
float turbidityArray[AVG_SAMPLES];
float tdsArray[AVG_SAMPLES];
int avgIndex = 0;
bool arrayFilled = false;

// -------------------- STATE MACHINE --------------------
enum DisplayMode { LIVE, LOCKED };
DisplayMode currentMode = LIVE;
unsigned long modeStartTime = 0;

float lockedTurbidity = 0;
float lockedTDS = 0;
bool lockedJustNow = false;

// -------------------- BLYNK BUZZER CONTROL --------------------
BLYNK_WRITE(V3) {
  int state = param.asInt(); // 1 or 0
  digitalWrite(BUZZER_PIN, state ? HIGH : LOW);
}

// ---------- Helper: calculate average ----------
float calculateAverage(float arr[], int size) {
  float sum = 0;
  for (int i = 0; i < size; i++) sum += arr[i];
  return sum / size;
}

// ================= SETUP =================
void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  // OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED NOT FOUND");
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  for (int i = 0; i < AVG_SAMPLES; i++) {
    turbidityArray[i] = 0;
    tdsArray[i] = 0;
  }

  // WiFi + Blynk
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  Serial.println("Connecting to Blynk...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);

  ThingSpeak.begin(client);

  modeStartTime = millis();

  Serial.println("\n=== TURBIDITY + TDS MONITOR ===");
  Serial.println("Cycle: 0.5s LIVE -> 2s LOCKED -> repeat");
  Serial.println("---");
  delay(2000);
}

// ================= LOOP =================
void loop() {
  Blynk.run(); // Run Blynk
  unsigned long currentTime = millis();
  lockedJustNow = false;

  // ---------- MODE SWITCH ----------
  if (currentMode == LIVE) {
    if (currentTime - modeStartTime >= LIVE_DURATION) {
      currentMode = LOCKED;
      modeStartTime = currentTime;

      int samplesToUse = arrayFilled ? AVG_SAMPLES : max(avgIndex, 1);
      lockedTurbidity = calculateAverage(turbidityArray, samplesToUse);
      lockedTDS = calculateAverage(tdsArray, samplesToUse);
      lockedJustNow = true;

      digitalWrite(BUZZER_PIN, HIGH);
      delay(100);
      digitalWrite(BUZZER_PIN, LOW);

      Serial.println("\n*** LOCKED ***");
      Serial.print("Turbidity: "); Serial.print((int)lockedTurbidity);
      Serial.print(" NTU | TDS: "); Serial.print((int)lockedTDS); Serial.println(" ppm");
      Serial.println("---");
    }
  } else {
    if (currentTime - modeStartTime >= LOCKED_DURATION) {
      currentMode = LIVE;
      modeStartTime = currentTime;
      avgIndex = 0;
      arrayFilled = false;

      Serial.println("\n*** LIVE MODE ***");
      Serial.println("---");
    }
  }

  // ---------- SENSOR READ ----------
  int turbidityRaw = analogRead(TURBIDITY_PIN);
  float turbidityVoltageESP32 = turbidityRaw * (3.3 / 4095.0);
  float turbiditySensorVoltage = turbidityVoltageESP32 * 2.0;

  float turbidity;
  if (turbiditySensorVoltage <= 0.5)
    turbidity = turbiditySensorVoltage * 100;
  else if (turbiditySensorVoltage <= 1.5)
    turbidity = 50 + (turbiditySensorVoltage - 0.5) * 450;
  else if (turbiditySensorVoltage <= 2.5)
    turbidity = 500 + (turbiditySensorVoltage - 1.5) * 500;
  else
    turbidity = 1000 + (turbiditySensorVoltage - 2.5) * 800;

  turbidity = constrain(turbidity, 0, 3000);

  int tdsRaw = analogRead(TDS_PIN);
  float tdsVoltage = tdsRaw * VREF / 4095.0;
  float tdsValue = (133.42 * pow(tdsVoltage, 3)
                  - 255.86 * pow(tdsVoltage, 2)
                  + 857.39 * tdsVoltage) * 0.5;
  if (tdsValue < 0) tdsValue = 0;

  // ---------- AVERAGING ----------
  if (currentMode == LIVE) {
    turbidityArray[avgIndex] = turbidity;
    tdsArray[avgIndex] = tdsValue;
    avgIndex++;
    if (avgIndex >= AVG_SAMPLES) {
      avgIndex = 0;
      arrayFilled = true;
    }
  }

  int samplesToUse = arrayFilled ? AVG_SAMPLES : max(avgIndex, 1);
  float turbidityAvg = calculateAverage(turbidityArray, samplesToUse);
  float tdsAvg = calculateAverage(tdsArray, samplesToUse);

  float displayTurbidity = (currentMode == LIVE) ? turbidityAvg : lockedTurbidity;
  float displayTDS = (currentMode == LIVE) ? tdsAvg : lockedTDS;

  // ---------- OLED DISPLAY ----------
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  if (currentMode == LIVE) {
    display.print("LIVE ");
    unsigned long elapsed = currentTime - modeStartTime;
    display.print(elapsed / 100);
    display.print("/5");
  } else {
    display.print("LOCKED ");
    unsigned long remaining = (LOCKED_DURATION - (currentTime - modeStartTime)) / 100;
    display.print(remaining / 10);
    display.print(".");
    display.print(remaining % 10);
    display.print("s");
  }

  display.setCursor(0, 12);
  display.print("Turbidity:");
  display.setTextSize(2);
  display.setCursor(0, 22);
  display.print((int)displayTurbidity);
  display.setTextSize(1);
  display.setCursor(70, 26);
  display.print("NTU ");

  display.setCursor(0, 40);
  display.print("TDS:");
  display.setTextSize(2);
  display.setCursor(0, 50);
  display.print((int)displayTDS);
  display.setTextSize(1);
  display.setCursor(70, 54);
  display.print("ppm ");

  display.display();

  // ---------- SERIAL MONITOR ----------
  Serial.print(currentMode == LIVE ? "LIVE | " : "LOCKED | ");
  Serial.print("Turbidity: "); Serial.print((int)displayTurbidity);
  Serial.print(" NTU | TDS: "); Serial.print((int)displayTDS); Serial.println(" ppm");

  // ---------- BLYNK VIRTUAL WRITE ----------
  Blynk.virtualWrite(V0, displayTDS);
  Blynk.virtualWrite(V1, displayTurbidity);

  // ---------- THINGSPEAK UPLOAD ----------
  if (millis() - lastUpload >= UPLOAD_INTERVAL) {
    lastUpload = millis();

    ThingSpeak.setField(1, turbidityAvg);   // Live Turbidity
    ThingSpeak.setField(2, tdsAvg);         // Live TDS
    ThingSpeak.setField(3, lockedTurbidity);
    ThingSpeak.setField(4, lockedTDS);

    int status = ThingSpeak.writeFields(channelID, writeAPIKey);
    if (status != 200) {
      Serial.print("ThingSpeak error: ");
      Serial.println(status);
    }
  }

  delay(100);
}