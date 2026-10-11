#include <Wire.h>
#include <Adafruit_MPR121.h>
#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif
Adafruit_MPR121 rowSensor;
Adafruit_MPR121 colSensor;
void setup() {
  Serial.begin(115200);
  while (!Serial);
  if (!rowSensor.begin(0x5A)) {
    Serial.println("MPR121 0x5A not found");
    while (1);
  }
  if (!colSensor.begin(0x5B)) {
    Serial.println("MPR121 0x5B not found");
    while (1);
  }
  rowSensor.setAutoconfig(true);
  colSensor.setAutoconfig(true);
  Serial.println("Ready");
}
void loop() {
  uint16_t rows = rowSensor.touched();
  uint16_t cols = colSensor.touched();
  bool detected = false;
  Serial.println("----------------");
  for (int r = 0; r < 12; r++) {
    if (rows & _BV(r)) {
      for (int c = 0; c < 12; c++) {
        if (cols & _BV(c)) {
          Serial.print("Grid Point: Row ");
          Serial.print(r);
          Serial.print("  Column ");
          Serial.println(c);
          detected = true;
        }
      }
    }
  }
  if (!detected) {
    Serial.println("No touch");
  }
  delay(100);
}