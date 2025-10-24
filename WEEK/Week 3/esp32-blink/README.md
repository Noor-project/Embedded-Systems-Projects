# 📘 Embedded Systems Project Documentation

## 🧾 Basic Information
- **Project Title:** ESP32-Blink
- **Week:** 3  
- **Author:** Noor Fatima  
- **Registration No:** 23-NTU-CS-1083  
- **Course:** Embedded Systems  

---

## 🧩 Project Overview
_Write a short description of what this project does._  
Example:  
> This project demonstrates how to use the ESP32 hardware timer to blink an LED every second using interrupts instead of delay.

---

## ⚙️ Components Used
List all hardware and software components you used.  
Example:

**Hardware:**
- ESP32 Development Board  
- LED  
- DHT11 Sensor / OLED Display / Buzzer (as applicable)  
- Jumper Wires, Breadboard  

**Software:**
- VS Code with PlatformIO  
- Arduino Framework  
- Git & GitHub for Version Control  

---

## 🔌 Circuit Connections
| ESP32 Pin | Component | Description |
|------------|------------|--------------|
| GPIO __ | __________ | __________ |
| GND | Ground | Common ground |

> 💡 Tip: Update the table above with your actual connections.

---

## 🧠 Code Explanation
Describe the main functions of your code in short points.  
Example:
1. Initializes sensors, displays, or timers.  
2. Reads data from input devices (sensors, switches).  
3. Processes the data or triggers actions.  
4. Displays or outputs the result.

---

## ▶️ How to Run
1. Open this folder in **VS Code / PlatformIO**.  
2. Connect your **ESP32 board** to your computer.  
3. Upload the code to the board.  
4. Open the **Serial Monitor** to view output (if applicable).  

---

## 📚 Learning Outcomes
- Learn how to program ESP32 peripherals.  
- Understand how to use timers, sensors, and displays.  
- Learn structured project documentation and GitHub management.

---

## 🧩 Example Code Snippet
```cpp
#include <Arduino.h>

#define LED_PIN 2
hw_timer_t *My_timer = nullptr;

void IRAM_ATTR onTimer() {
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  My_timer = timerBegin(0, 80, true);
  timerAttachInterrupt(My_timer, &onTimer, true);
  timerAlarmWrite(My_timer, 1000000, true);
  timerAlarmEnable(My_timer);
}

void loop() {
  // main loop is free
}
