//NOOR FATIMA
//23-NTU-CS-1083
//Date: 10th Sept 2024
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ==================== OLED Setup ====================
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ==================== Pin Definitions ====================
#define LED1 2
#define LED2 4
#define LED3 5
#define BUZZER 27
#define BTN_MODE 12
#define BTN_RESET 14

// ==================== Variables ====================
// Used for debouncing the interrupts
volatile unsigned long lastModeInterrupt = 0;
volatile unsigned long lastResetInterrupt = 0;
const unsigned long debounceDelay = 250;  // debounce time in ms

// Flags set by interrupts (read in main loop)
volatile bool modePressed = false;
volatile bool resetPressed = false;

// Mode control variables
int mode = 0;                  // Current LED mode (0–3)
unsigned long lastBlinkTime = 0;
int blinkState = 0;
int fadeValue = 0;
int fadeDir = 1;               // 1 = fade in, -1 = fade out

// ==================== OLED Helper Function ====================
// Displays text messages on the OLED
void showMessage(String msg) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 25);
  display.println(msg);
  display.display();
}

// ==================== Interrupt Service Routines ====================
// ISR for MODE button
void IRAM_ATTR handleModePress() {
  unsigned long currentTime = millis();
  // Debounce check
  if (currentTime - lastModeInterrupt > debounceDelay) {
    modePressed = true;               // Set flag for main loop
    lastModeInterrupt = currentTime;  // Update debounce timer
  }
}

// ISR for RESET button
void IRAM_ATTR handleResetPress() {
  unsigned long currentTime = millis();
  // Debounce check
  if (currentTime - lastResetInterrupt > debounceDelay) {
    resetPressed = true;              // Set flag for main loop
    lastResetInterrupt = currentTime; // Update debounce timer
  }
}

// ==================== Setup Function ====================
void setup() {
  // Configure pin modes
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BTN_MODE, INPUT_PULLUP);
  pinMode(BTN_RESET, INPUT_PULLUP);

  // Initialize serial monitor
  Serial.begin(115200);

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED initialization failed!"));
    while (1);
  }

  // Attach interrupts (triggered on falling edge)
  attachInterrupt(digitalPinToInterrupt(BTN_MODE), handleModePress, FALLING);
  attachInterrupt(digitalPinToInterrupt(BTN_RESET), handleResetPress, FALLING);

  // Display startup message
  showMessage("Mode 0: Both OFF");
  Serial.println("System Ready - Mode 0 (Both OFF)");
}

// ==================== Main Loop ====================
void loop() {
  // -------- Handle MODE Button Press --------
  if (modePressed) {
    modePressed = false;              // Clear flag
    mode = (mode + 1) % 4;            // Cycle through modes (0–3)
    tone(BUZZER, 1200, 80);           // Short beep for feedback

    // Display mode info on OLED
    String msg;
    switch (mode) {
      case 0: msg = "Mode 0: Both OFF"; break;
      case 1: msg = "Mode 1: Alternate Blink"; break;
      case 2: msg = "Mode 2: Both ON"; break;
      case 3: msg = "Mode 3: PWM Fade"; break;
    }
    showMessage(msg);
    Serial.println(msg);
  }

  // -------- Handle RESET Button Press --------
  if (resetPressed) {
    resetPressed = false;             // Clear flag
    mode = 0;                         // Reset to mode 0
    tone(BUZZER, 800, 100);           // Short lower-pitch beep
    showMessage("Reset → Mode 0: OFF");
    Serial.println("System Reset to Mode 0");
  }

  // -------- LED Behavior Based on Mode --------
  unsigned long currentTime = millis();

  switch (mode) {
    // --- Mode 0: All LEDs OFF ---
    case 0:
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      break;

    // --- Mode 1: Alternate Blinking LEDs ---
    case 1:
      if (currentTime - lastBlinkTime > 400) {  // Toggle every 400ms
        lastBlinkTime = currentTime;
        blinkState = !blinkState;
        digitalWrite(LED1, blinkState);
        digitalWrite(LED2, !blinkState);
      }
      break;

    // --- Mode 2: Both LEDs ON ---
    case 2:
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      break;

    // --- Mode 3: PWM Fade on LED3 ---
    case 3:
      analogWrite(LED3, fadeValue);
      fadeValue += fadeDir * 5;  // Smooth fade step
      if (fadeValue <= 0 || fadeValue >= 255)
        fadeDir = -fadeDir;      // Reverse fade direction
      delay(10);                 // Smooth visual fade (interrupts still work)
      break;
  }
}
