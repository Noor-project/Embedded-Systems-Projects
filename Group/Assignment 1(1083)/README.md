Assignment 1 — LED & Button Control with OLED

Student: Noor Fatima | Reg No: 23-NTU-CS-1083
Course: Embedded Systems / Microcontroller Programming

Project Overview

Task A — Multi-Mode LED Controller

Two buttons: MODE & RESET

4 modes: Both OFF, Alternate Blink, Both ON, PWM Fade

OLED shows current mode; buzzer gives feedback

Task B — Single Button Press Detection

Short press (<1.5s): toggle LED

Long press (>1.5s): buzzer tone

OLED displays event

Hardware

ESP32, LEDs, Buzzer, Push Buttons, OLED (128x64), Breadboard & wires

Pins
Component	Pin
LED1	GPIO 2
LED2	GPIO 4
LED3	GPIO 5
Buzzer	GPIO 27
Button	GPIO 12
Reset Btn	GPIO 14
OLED SDA	GPIO 21
OLED SCL	GPIO 22
Setup

Connect hardware as per pin table

Load code from /src/

Install Adafruit_GFX & Adafruit_SSD1306

Upload to ESP32 and run

Simulation

Task A: https://wokwi.com/projects/443969516831808513

Task B: https://wokwi.com/projects/445885024042885121