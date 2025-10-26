  Title       : LED Mode Controller with OLED Display (Interrupt + Debounce)
  Author      : Noor Fatima
  Registration: 23-NTU-CS-1083
  Board       : ESP32 (Compatible with Wokwi)
  Date        : October 2025
  =========================================================================
  📘 Description:
  This project controls 3 LEDs, a buzzer, and an OLED display using two buttons.
  It demonstrates the use of **interrupts**, **software debouncing**, and 
  **OLED feedback** on an ESP32 board.

  ➤ Button 1 (MODE):
      • Cycles through 4 LED modes (each shown on OLED)
          0 → Both OFF
          1 → Alternate Blink
          2 → Both ON
          3 → PWM Fade Effect

  ➤ Button 2 (RESET):
      • Resets back to Mode 0 (All OFF)

  ➤ OLED Display:
      • Shows the current mode or event message.

  ➤ Buzzer:
      • Beeps briefly on each button press as feedback.

  Hardware Connections:
  -------------------------------------------------------------------------
   Component   | ESP32 Pin | Description
  -------------|------------|----------------------------------------------
   LED1        | GPIO 2     | First LED (mode indication)
   LED2        | GPIO 4     | Second LED (mode indication)
   LED3        | GPIO 5     | PWM fade LED
   BUZZER      | GPIO 27    | Active buzzer
   BTN_MODE    | GPIO 12    | Mode cycle button
   BTN_RESET   | GPIO 14    | Reset button
   OLED SDA    | GPIO 21    | I2C SDA
   OLED SCL    | GPIO 22    | I2C SCL
LINK
https://wokwi.com/projects/443969516831808513