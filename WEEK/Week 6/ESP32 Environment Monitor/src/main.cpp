//NOOR FATIMA
//23-NTU-CS-1083
//BSCS 5TH A
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// --- Pin configuration ---
#define DHTPIN 14         // DHT22 data pin
#define DHTTYPE DHT22     // Change to DHT11 if needed
#define LDR_PIN 34        // LDR analog pin
#define SDA_PIN 21        // OLED SDA
#define SCL_PIN 22        // OLED SCL

// --- OLED setup ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// --- DHT sensor setup ---
DHT dht(DHTPIN, DHTTYPE);

// --- Setup function ---
void setup() {
  Serial.begin(115200);
  Serial.println("Starting ESP32 Environment Monitor...");

  // Initialize I2C
  Wire.begin(SDA_PIN, SCL_PIN);

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed!");
    for (;;);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Initializing...");
  display.display();

  // Initialize DHT sensor
  dht.begin();
  delay(1000);
}

// --- Main loop ---
void loop() {
  // --- Read sensors ---
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int ldrValue = analogRead(LDR_PIN);
  float lightVoltage = (ldrValue / 4095.0) * 3.3;

  // --- Validate DHT readings ---
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT22 sensor!");
    return;
  }

  // --- Serial Monitor output ---
  Serial.printf("Temp: %.2f°C | Humidity: %.2f%% | LDR: %d (%.2f V)\n",
                temperature, humidity, ldrValue, lightVoltage);

  // --- Display on OLED ---
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Home Task - Week 6");

  display.setCursor(0, 16);
  display.print("Temp: ");
  display.print(temperature, 1);
  display.println(" C");

  display.setCursor(0, 28);
  display.print("Humidity: ");
  display.print(humidity, 1);
  display.println(" %");

  display.setCursor(0, 40);
  display.print("Light: ");
  display.print(lightVoltage, 2);
  display.println(" V");

  display.display();

  delay(2000); // Update every 2 seconds
}
