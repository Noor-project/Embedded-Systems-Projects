# 💡 ESP32 Combined Project – LED Fade & Buzzer Patterns

## 🧾 Basic Information
- **Project Title:** ESP32 Combined – LED Fade & Buzzer Patterns  
- **Week:** 5  
- **Author:** Noor Fatima  
- **Registration No:** 23-NTU-CS-1083  
- **Course:** Embedded Systems Lab  

---

## 🧩 Project Overview
This project demonstrates controlling **LEDs with PWM fading** while simultaneously generating **buzzer sound patterns** using an ESP32.  

The program includes:  
1. Opposite fading of two LEDs (PWM brightness)  
2. Buzzer patterns:  
   - Loud beeps  
   - Frequency sweep  
   - Short melody  

---

## ⚙️ Components Used

**Hardware:**
- ESP32 Development Board  
- 2 LEDs  
- 1 Resistor per LED (220–330Ω)  
- Active Buzzer or Piezo Speaker  
- Jumper Wires  

**Software:**
- Arduino IDE / PlatformIO  
- Arduino core for ESP32  

---

## 🔌 Circuit Connections

| Component | ESP32 Pin | Description |
|-----------|-----------|-------------|
| LED1      | GPIO 18  | PWM fading |
| LED2      | GPIO 19  | Opposite PWM fading |
| Buzzer    | GPIO 27  | PWM tone output |

> 💡 Tip: Add current-limiting resistors to LEDs to prevent damage.

---

## 🧠 Code Explanation

### 1. LED Configuration
```cpp
#define LED1_PIN 18
#define LED2_PIN 19
#define LED1_CH  0
#define LED2_CH  1
#define LED_FREQ 5000
#define LED_RES  8
