# 🌡️ ESP32 Environment Monitor (DHT22 + OLED)

## 🧾 Basic Information
- **Project Title:** ESP32 Environment Monitor  
- **Week:** 6  
- **Author:** Noor Fatima  
- **Registration No:** 23-NTU-CS-1083  
- **Course:** Embedded Systems Lab  

---

## 🧩 Project Overview
This project demonstrates how to read **temperature and humidity** from a **DHT22 sensor** and display the data on an **OLED screen** using an ESP32.  
The readings are also printed on the Serial Monitor.

---

## ⚙️ Components Used

**Hardware:**
- ESP32 Development Board  
- DHT22 Sensor (or DHT11)  
- SSD1306 OLED Display (128x64)  
- Jumper Wires  

**Software:**
- Arduino IDE / PlatformIO  
- Libraries: `Adafruit_GFX`, `Adafruit_SSD1306`, `DHT`  

---

## 🔌 Circuit Connections

| Component    | ESP32 Pin | Description |
|--------------|-----------|-------------|
| DHT22 Data   | GPIO 14   | Connect with 10kΩ pull-up resistor |
| OLED SDA     | GPIO 21   | I2C SDA |
| OLED SCL     | GPIO 22   | I2C SCL |
| VCC / GND    | 3.3V / GND | Power and ground |

> 💡 Tip: Ensure correct wiring of I2C pins (SDA & SCL) and pull-up resistor for DHT22.

---

## 🧠 Code Explanation

### 1. Sensor and Display Setup
```cpp
DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Wire.begin(SDA_PIN, SCL_PIN);
