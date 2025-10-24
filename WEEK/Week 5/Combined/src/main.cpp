#include <Arduino.h>

// --- LED Configuration ---
#define LED1_PIN 18
#define LED2_PIN 19
#define LED1_CH  0
#define LED2_CH  1
#define LED_FREQ 5000
#define LED_RES  8

// --- Buzzer Configuration ---
#define BUZZER_PIN 27
#define BUZZER_CH  2
#define BUZZER_RES 10     // 10-bit => 0–1023
#define BUZZER_VOLUME 800 // Higher = louder (max 1023)

void setup() {
  // --- Setup LEDs ---
  ledcSetup(LED1_CH, LED_FREQ, LED_RES);
  ledcAttachPin(LED1_PIN, LED1_CH);

  ledcSetup(LED2_CH, LED_FREQ, LED_RES);
  ledcAttachPin(LED2_PIN, LED2_CH);

  // --- Setup Buzzer ---
  ledcSetup(BUZZER_CH, 2000, BUZZER_RES);
  ledcAttachPin(BUZZER_PIN, BUZZER_CH);
}

void playTone(int freq, int duration) {
  ledcWriteTone(BUZZER_CH, freq);       // set frequency
  ledcWrite(BUZZER_CH, BUZZER_VOLUME);  // set loudness
  delay(duration);
  ledcWrite(BUZZER_CH, 0);              // turn off
}

void loop() {
  // --- LED Fade Cycle ---
  for (int d = 0; d <= 255; d++) {
    ledcWrite(LED1_CH, d);
    ledcWrite(LED2_CH, 255 - d);  // Opposite fade
    delay(8);
  }
  for (int d = 255; d >= 0; d--) {
    ledcWrite(LED1_CH, d);
    ledcWrite(LED2_CH, 255 - d);
    delay(8);
  }

  // --- Repeating Buzzer Pattern ---
  // 1. Three loud beeps
  for (int i = 0; i < 3; i++) {
    playTone(2000 + i * 300, 150);
    delay(150);
  }

  // 2. Frequency sweep
  for (int f = 400; f <= 3000; f += 150) {
    playTone(f, 20);
  }

  // 3. Melody
  int melody[] = {262, 294, 330, 392, 523};
  for (int i = 0; i < 5; i++) {
    playTone(melody[i], 250);
  }

  ledcWrite(BUZZER_CH, 0); // Stop buzzer
  delay(500);
}