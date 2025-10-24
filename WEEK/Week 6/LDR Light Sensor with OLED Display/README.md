# 🌞 ESP32 LDR Monitor with OLED Display

## 🧾 Basic Information
- **Project Title:** ESP32 LDR Light Sensor Monitor  
- **Author:** Noor Fatima  
- **Registration No:** 23-NTU-CS-1083  
- **Course:** Embedded Systems Lab  

---

## 🧩 Project Overview
This project reads light intensity using an **LDR (Light Dependent Resistor)** and displays the **ADC value** and corresponding **voltage** on a **128x64 OLED display**. Values are also printed to the **Serial Monitor** for logging or analysis.

---

## ⚙️ Components Used

**Hardware:**
- ESP32 Development Board  
- LDR Sensor  
- SSD1306 OLED Display (128x64)  
- 10kΩ resistor (for LDR voltage divider)  
- Jumper Wires  

**Software:**
- Arduino IDE  
- Libraries: `Adafruit_GFX`, `Adafruit_SSD1306`  

---

## 🔌 Circuit Connections

| Component      | ESP32 Pin | Description |
|----------------|-----------|-------------|
| LDR Analog     | GPIO 34   | Connected to analog pin |
| OLED SDA       | GPIO 21   | I2C SDA |
| OLED SCL       | GPIO 22   | I2C SCL |
| VCC / GND      | 3.3V / GND | Power and ground |

> 💡 Note: Use a voltage divider with the LDR for better voltage readings (LDR + 10kΩ resistor).

---

## 🧠 Code Explanation

### 1. OLED and I2C Initialization
```cpp
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Wire.begin(SDA_PIN, SCL_PIN);
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
display.clearDisplay();
display.setTextColor(SSD1306_WHITE);
