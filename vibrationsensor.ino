void setup() {
  pinMode(3, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  // 100 Hz for 5 seconds
  unsigned long startTime = millis();

  while (millis() - startTime < 5000) {
    digitalWrite(3, HIGH);
    delayMicroseconds(5000);
    digitalWrite(3, LOW);
    delayMicroseconds(5000);
  }

  // 180 Hz for 5 seconds
  // Half-period = 1/(2 × 180) = 2778 microseconds
  startTime = millis();

  while (millis() - startTime < 5000) {
    digitalWrite(3, HIGH);
    delayMicroseconds(2778);
    digitalWrite(3, LOW);
    delayMicroseconds(2778);
  }
}
