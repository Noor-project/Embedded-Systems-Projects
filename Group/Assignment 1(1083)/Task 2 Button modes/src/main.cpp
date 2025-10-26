//Noor Fatima
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
#define LED_PIN 2
#define BUZZER_PIN 27
#define BUTTON_PIN 12

// ==================== Timing & State Variables ====================
unsigned long pressStartTime = 0;  // Timestamp when button is pressed
bool buttonPressed = false;        // Tracks if button is currently held
bool ledState = false;             // Stores LED ON/OFF state

// ==================== OLED Helper Function ====================
// Displays messages on the OLED screen
void showMessage(const String &msg) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 25);
  display.println(msg);
  display.display();
}

// ==================== Setup Function ====================
void setup() {
  // Configure pin modes
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Button is active LOW

  Serial.begin(115200);

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED initialization failed!"));
    while (1);
  }

  // Initial message and LED state
  showMessage("Press Button...");
  digitalWrite(LED_PIN, LOW);
}

// ==================== Main Loop ====================
void loop() {
  bool buttonState = digitalRead(BUTTON_PIN);

  // -------- Detect Button Press (Start of Press) --------
  if (buttonState == LOW && !buttonPressed) {
    buttonPressed = true;           // Mark button as pressed
    pressStartTime = millis();       // Record the press start time
  }

  // -------- Detect Button Release (End of Press) --------
  if (buttonState == HIGH && buttonPressed) {
    buttonPressed = false;           // Clear pressed state
    unsigned long pressDuration = millis() - pressStartTime; // Calculate duration

    // --- Short Press: Toggle LED ---
    if (pressDuration < 1500) {
      ledState = !ledState;                     // Toggle LED state
      digitalWrite(LED_PIN, ledState);          // Apply new LED state
      showMessage("Short Press → LED " + String(ledState ? "ON" : "OFF")); // OLED feedback
      tone(BUZZER_PIN, 1200, 60);              // Small beep for confirmation
      Serial.println("Short Press Detected");
    }

    // --- Long Press: Play Buzzer Tone ---
    else {
      showMessage("Long Press → Buzzer");      // OLED feedback
      tone(BUZZER_PIN, 1000);                  // Start buzzer tone
      delay(600);                              // Play tone for 0.6s
      noTone(BUZZER_PIN);                      // Stop tone
      Serial.println("Long Press Detected");
    }
  }

  delay(20); // Small delay for debounce and CPU relief
}
