# 🔊 ESP32 Buzzer – PWM Sound Patterns

## 🧾 Basic Information
- **Project Title:** ESP32 Buzzer – PWM Sound Patterns  
- **Week:** 5  
- **Author:** Noor Fatima  
- **Registration No:** 23-NTU-CS-1083  
- **Course:** Embedded Systems Lab  

---

## 🧩 Project Overview
This project demonstrates generating **sound patterns** using a **buzzer** connected to the ESP32 with **PWM (Pulse Width Modulation)**.  

The program includes:  
1. Simple beep pattern  
2. Frequency sweep from 400 Hz to 3000 Hz  
3. Short melody (C major scale)  

PWM allows precise control of buzzer tones without blocking the main program.

---

## ⚙️ Components Used

**Hardware:**
- ESP32 Development Board  
- Active Buzzer or Piezo Speaker  
- Jumper Wires  

**Software:**
- Arduino IDE / PlatformIO  
- Arduino core for ESP32  

---

## 🔌 Circuit Connections

| Component | ESP32 Pin | Description |
|-----------|-----------|-------------|
| Buzzer    | GPIO 27   | Connect + to GPIO, - to GND |

> 💡 Tip: Active buzzers generate sound with a simple HIGH/LOW signal, but this project uses PWM for precise tone control.

---

## 🧠 Code Explanation

### 1. Define Buzzer Pin and PWM
```cpp
#define BUZZER_PIN  27
#define PWM_CH      0
#define FREQ        2000
#define RESOLUTION  10
