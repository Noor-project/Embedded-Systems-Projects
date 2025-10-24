# 💡 ESP32 LED Blink using Hardware Timer

## 🧾 Basic Information
- **Project Title:** LED Blink using Hardware Timer  
- **Week:** 4  
- **Author:** Noor Fatima  
- **Registration No:** 23-NTU-CS-1083  
- **Course:** Embedded Systems Lab  

---

## 🧩 Project Overview
This project demonstrates how to blink an **LED** on the **ESP32** using a **hardware timer interrupt**. Unlike `delay()`-based blinking, hardware timers allow the main loop to remain free for other tasks.  

The program:
1. Configures a hardware timer on the ESP32.  
2. Sets an interrupt to toggle the LED every 1 second.  
3. Keeps the `loop()` function free for additional code.

---

## ⚙️ Components Used

**Hardware:**
- ESP32 Development Board  
- LED (built-in or external)  
- Resistor (if using external LED, ~220Ω)  

**Software:**
- Arduino IDE / PlatformIO  
- Arduino core for ESP32  

---

## 🔌 Circuit Connections

| Component | ESP32 Pin | Description |
|-----------|-----------|-------------|
| LED       | GPIO 2    | Built-in or external with series resistor |

> 💡 Note: Most ESP32 boards have a built-in LED on **GPIO 2**.

---

## 🧠 Code Explanation

### 1. Define LED Pin & Timer
```cpp
#define LED_PIN 2
hw_timer_t *My_timer = nullptr;
