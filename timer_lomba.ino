#include <TM1637Display.h>

const int CLK = 6;
const int DIO = 7;
TM1637Display display(CLK, DIO);

// Tombol dan sensor
const int buttonPin = 4;
const int irSensorPin = 2;

// LED
const int ledRed = 8;
const int ledYellow = 9;
const int ledGreen = 10;

unsigned long startTime = 0;
unsigned long stopTime = 0;
bool timerRunning = false;

int buttonState = 0;
int lastButtonState = 0;
int pressCount = 0;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 300;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(irSensorPin, INPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  display.setBrightness(0x0f);
  display.showNumberDecEx(0, 0b01000000, true);
}

void loop() {
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        pressCount++;
        handlePress();
      }
    }
  }

  lastButtonState = reading;

  if (timerRunning) {
    unsigned long elapsed = (millis() - startTime) / 1000;
    int minutes = elapsed / 60;
    int seconds = elapsed % 60;
    display.showNumberDecEx(minutes * 100 + seconds, 0b01000000, true);
  }
}

void handlePress() {
  if (pressCount == 1) {
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledGreen, LOW);
  } else if (pressCount == 2) {
    digitalWrite(ledRed, LOW);
    digitalWrite(ledYellow, HIGH);
    digitalWrite(ledGreen, LOW);
  } else if (pressCount == 3) {
    digitalWrite(ledRed, LOW);
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledGreen, HIGH);
    startTime = millis();
    timerRunning = true;
  }

  // Jika IR sensor aktif dan timer sedang berjalan
  if (timerRunning && digitalRead(irSensorPin) == LOW) {
    stopTime = millis();
    timerRunning = false;
    showFinalTime((stopTime - startTime) / 1000);
    pressCount = 0; // reset
  }
}

void showFinalTime(unsigned long seconds) {
  int minutes = seconds / 60;
  int secs = seconds % 60;
  display.showNumberDecEx(minutes * 100 + secs, 0b01000000, true);
}
