#include <math.h>

const int THERMISTOR_PIN = A1;

const float SERIES_RESISTOR = 1000.0;   // 1 kΩ
const float NOMINAL_RESISTANCE = 10000.0; // 10 kΩ at 25°C
const float NOMINAL_TEMPERATURE = 25.0; // °C
const float BETA = 3950.0;
const float ADC_MAX = 1023.0;

void setup() {
  Serial.begin(9600);
}

void loop() {

  int rawValue = analogRead(THERMISTOR_PIN);

  // Voltage at the divider
  float voltage = rawValue * 5.0 / ADC_MAX;

  // For: 5V -> thermistor -> A0 -> 1k resistor -> GND
  float resistance = SERIES_RESISTOR * voltage / (5.0 - voltage);

  // Beta equation
  float steinhart;
  steinhart = resistance / NOMINAL_RESISTANCE;
  steinhart = log(steinhart);
  steinhart /= BETA;
  steinhart += 1.0 / (NOMINAL_TEMPERATURE + 273.15);
  steinhart = 1.0 / steinhart;
  steinhart -= 273.15;

  Serial.print("Raw: ");
  Serial.print(rawValue);

  Serial.print(" | Resistance: ");
  Serial.print(resistance);
  Serial.print(" ohms");

  Serial.print(" | Temperature: ");
  Serial.print(steinhart);
  Serial.println(" °C");

  delay(500);
}