#include "LedControl.h"

LedControl leds = LedControl(2, 4, 3, 3);

void setup() {
  for (int i = 0; i < leds.getDeviceCount(); i++) {
    leds.shutdown(i, false);
    leds.clearDisplay(i);
  }

  Serial.begin(1000000);
}

void loop() {
  if (Serial.available()) {
    String line = Serial.readStringUntil('\n');
    for (int i = 0; i < line.length(); i += 2) {
      int x = i / 2;
      int y = (int) line.charAt(i) - '0';
      byte val = 0;
      for (int j = 0; j <= y; j++) {
        val ^= (1 << j);
      }
      if (x > 15) {
        leds.setRow(2, x-16, val);
      } else if (x > 7) {
        leds.setRow(1, 15-x, val);
      } else {
        leds.setRow(0, x, val);
      }
    }
  }
}