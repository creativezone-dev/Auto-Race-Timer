# Arduino Race Timer with IR Sensor & LED Indicator

This project is a simple race timer using an Arduino UNO, an IR sensor, and a TM1637 4-digit 7-segment display.  
It also includes a button with multi-press logic and LED indicators to guide the race phases.

## 🛠 Features
- Start/Stop timer using a tactile push button
- IR sensor to detect finish (stop timer)
- Timer displayed in MM:SS format
- 3-step LED indicator:
  - 🔴 Red: First button press (ready)
  - 🟡 Yellow: Second press (set)
  - 🟢 Green: Third press (go — timer starts)
- Debounce protection to prevent double reading

## 🔌 Hardware Used
- Arduino Uno
- TM1637 7-segment display
- IR sensor module (digital out)
- Tactile button
- 3x LEDs (Red, Yellow, Green)
- 220Ω resistors for LEDs
- Optional: LiPo battery or 5V USB power

## 📷 Example Wiring

IR sensor  → D2
Button     → D4
TM1637 CLK → D6
TM1637 DIO → D7
LED Red    → D8
LED Yellow → D9
LED Green  → D10

## 🧠 How It Works
1. Press the button → LED Red on (Ready)
2. Press again → LED Yellow on (Set)
3. Press a third time → LED Green on + Timer starts (Go!)
4. When IR sensor is triggered → Timer stops and final time is shown
5. Press button again to restart the cycle

## 📝 Author
Created by [creativezone], as part of portfolio for Arduino freelance & embedded systems.

---


