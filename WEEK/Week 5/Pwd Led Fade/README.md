# 💡 ESP32 PWM LED Brightness Fade

## 🧾 Basic Information
- **Project Title:** ESP32 PWM LED Fade  
- **Week:** 5  
- **Author:** Noor Fatima  
- **Registration No:** 23-NTU-CS-1083  
- **Course:** Embedded Systems Lab  

---

## 🧩 Project Overview
This project demonstrates how to control **LED brightness** using **PWM (Pulse Width Modulation)** on an ESP32. The LED gradually fades **up and down** in brightness.

---

## ⚙️ Components Used

**Hardware:**
- ESP32 Development Board  
- 1 LED  
- 1 Resistor (220–330Ω)  
- Jumper Wires  

**Software:**
- Arduino IDE / PlatformIO  
- Arduino core for ESP32  

---

## 🔌 Circuit Connections

| Component | ESP32 Pin | Description |
|-----------|-----------|-------------|
| LED       | GPIO 18   | PWM brightness control |
| Resistor  | In series | Current limiting (220–330Ω) |

> 💡 Tip: Always use a current-limiting resistor with LEDs to prevent damage.

---

## 🧠 Code Explanation

### 1. PWM Setup
```cpp
#define LED_PIN 18
#define PWM_CH 0
#define FREQ 5000
#define RES 8
