# 🌡️ ESP32 Environment Monitor with DHT22 & LDR

## 🧾 Basic Information
- **Project Title:** ESP32 Environment Monitor (DHT22 + LDR + OLED)  
- **Week:** 6  
- **Author:** Noor Fatima  
- **Registration No:** 23-NTU-CS-1083  
- **Course:** Embedded Systems Lab  

---

## 🧩 Project Overview
This project reads **temperature and humidity** from a **DHT22 sensor** and **ambient light intensity** from an **LDR**. The readings are displayed on an **OLED display** and printed to the Serial Monitor.  

This is a practical IoT example for **environment monitoring**.

---

## ⚙️ Components Used

**Hardware:**
- ESP32 Development Board  
- DHT22 Sensor (or DHT11)  
- LDR Sensor  
- SSD1306 OLED Display (128x64)  
- 10kΩ resistor for LDR voltage divider (if needed)  
- Jumper Wires  

**Software:**
- Arduino IDE / PlatformIO  
- Libraries: `DHT`, `Adafruit_GFX`, `Adafruit_SSD1306`  

---

## 🔌 Circuit Connections

| Component      | ESP32 Pin | Description |
|----------------|-----------|-------------|
| DHT22 Data     | GPIO 14   | Data pin with pull-up resistor |
| LDR Sensor     | GPIO 34   | Analog input |
| OLED SDA       | GPIO 21   | I2C SDA |
| OLED SCL       | GPIO 22   | I2C SCL |
| VCC / GND      | 3.3V / GND | Power and ground |

> 💡 Tip: Use a voltage divider with the LDR to ensure proper analog readings.

---

## 🧠 Code Explanation

### 1. Sensor and Display Setup
```cpp
DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Wire.begin(SDA_PIN, SCL_PIN);
