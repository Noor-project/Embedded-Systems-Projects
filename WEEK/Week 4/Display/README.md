# 🖥️ ESP32 OLED Display Text and Graphics

## 🧾 Basic Information
- **Project Title:** OLED Display – Text & Graphics Demo  
- **Week:** 4  
- **Author:** Noor Fatima  
- **Registration No:** 23-NTU-CS-1083  
- **Course:** Embedded Systems Lab  

---

## 🧩 Project Overview
This project demonstrates how to use an **SSD1306-based 0.96” OLED display** with the **ESP32** to show text and simple graphics using the **Adafruit GFX** and **Adafruit SSD1306** libraries.  

The program:
1. Initializes the OLED display over the I²C interface.  
2. Draws two diagonal lines across the screen.  
3. Displays “Hello” and “CS-A” text messages with different font sizes.  

---

## ⚙️ Components Used

**Hardware:**
- ESP32 Development Board  
- 0.96” I2C OLED Display (SSD1306 driver)  
- Jumper wires  

**Software:**
- VS Code with PlatformIO (or Arduino IDE)  
- Adafruit GFX Library  
- Adafruit SSD1306 Library  
- Wire (I2C communication)

---

## 🔌 Circuit Connections

| OLED Pin | ESP32 Pin | Description |
|-----------|------------|--------------|
| VCC       | 3.3V       | Power supply |
| GND       | GND        | Ground |
| SDA       | GPIO 21    | I2C Data |
| SCL       | GPIO 22    | I2C Clock |

> 💡 Note: Most ESP32 boards use **GPIO 21 (SDA)** and **GPIO 22 (SCL)** by default for I2C.

---

## 🧠 Code Explanation

### 1. Include Required Libraries
```cpp
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
