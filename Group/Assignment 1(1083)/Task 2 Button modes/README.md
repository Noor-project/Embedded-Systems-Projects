 Title       : Single Button Press-Type Detection with OLED Display
  Author      : Noor Fatima
  Registration: 23-NTU-CS-1083
  Board       : ESP32 (Wokwi compatible)
  Task B      : Detect Short and Long Button Press

  📘 Description:
  This program detects two types of button presses using a single button:
  1. Short Press → Toggle LED
  2. Long Press  → Play Buzzer Tone
  The OLED display provides real-time feedback for the event.

  =========================================================================
  Hardware Connections:
  -------------------------------------------------------------------------
   Component   | ESP32 Pin | Description
  -------------|------------|----------------------------------------------
   LED         | GPIO 2     | Toggle LED for short press feedback
   BUZZER      | GPIO 27    | Beep for short press or long press tone
   BUTTON      | GPIO 12    | Single button (active LOW)
   OLED SDA    | GPIO 21    | I2C SDA
   OLED SCL    | GPIO 22    | I2C SCL

   Link
  https://wokwi.com/projects/445885024042885121
