# 🖥️ ESP32 OLED Display – Name & Registration Number

## 🧾 Basic Information
- **Project Title:** OLED Display – Name & Registration Number  
- **Week:** 4  
- **Author:** Noor Fatima  
- **Registration No:** 23-NTU-CS-1083  
- **Course:** Embedded Systems Lab  

---

## 🧩 Project Overview
This project demonstrates how to use an **SSD1306-based 0.96” OLED display** with the **ESP32** to display personalized text (name and registration number) using the **Adafruit GFX** and **Adafruit SSD1306** libraries.

The program:
1. Initializes the OLED display over I²C communication.  
2. Clears the display and sets text size, color, and cursor position.  
3. Prints the user’s **name** and **registration number** on the OLED screen.

---

## ⚙️ Components Used

**Hardware:**
- ESP32 Development Board  
- 0.96” I2C OLED Display (SSD1306 driver)  
- Jumper Wires  

**Software:**
- VS Code with PlatformIO / Arduino IDE  
- Adafruit GFX Library  
- Adafruit SSD1306 Library  
- Wire Library for I2C communication  

---

## 🔌 Circuit Connections

| OLED Pin | ESP32 Pin | Description |
|-----------|------------|--------------|
| VCC       | 3.3V       | Power Supply |
| GND       | GND        | Ground |
| SDA       | GPIO 21    | I2C Data |
| SCL       | GPIO 22    | I2C Clock |

> 💡 Tip: Most ESP32 boards use **GPIO 21 (SDA)** and **GPIO 22 (SCL)** as default I²C pins.

---

## 🧠 Code Explanation

### 1. Include Required Libraries
```cpp
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
