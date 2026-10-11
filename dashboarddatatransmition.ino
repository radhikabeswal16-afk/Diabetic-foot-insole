                                                                                                                                                                                              // ============================================================
// ESP32 O-MAT
// 7 x 14 Velostat Pressure Matrix
// 2 x CD74HC4067
// ============================================================

// ---------------- MATRIX SIZE ----------------

const uint8_t N_ROWS = 7;
const uint8_t N_COLS = 16;


// ============================================================
// ROW MUX
// ============================================================

const uint8_t R_S0 = 16;
const uint8_t R_S1 = 17;
const uint8_t R_S2 = 18;
const uint8_t R_S3 = 19;


// ============================================================
// COLUMN MUX
// ============================================================

const uint8_t C_S0 = 21;
const uint8_t C_S1 = 22;
const uint8_t C_S2 = 23;
const uint8_t C_S3 = 25;


// ============================================================
// ADC
// ============================================================

const uint8_t ADC_PIN = 34;


// ============================================================
// SET ROW MUX
// ============================================================

void selectRow(uint8_t channel)
{
  digitalWrite(R_S0, channel & 0x01);
  digitalWrite(R_S1, (channel >> 1) & 0x01);
  digitalWrite(R_S2, (channel >> 2) & 0x01);
  digitalWrite(R_S3, (channel >> 3) & 0x01);
}


// ============================================================
// SET COLUMN MUX
// ============================================================

void selectColumn(uint8_t channel)
{
  digitalWrite(C_S0, channel & 0x01);
  digitalWrite(C_S1, (channel >> 1) & 0x01);
  digitalWrite(C_S2, (channel >> 2) & 0x01);
  digitalWrite(C_S3, (channel >> 3) & 0x01);
}


// ============================================================
// READ ONE SENSOR
// ============================================================

int readSensor(uint8_t row, uint8_t col)
{
  // Select row
  selectRow(row);

  // Select column
  selectColumn(col);

  // Allow the analog signal to settle
  delayMicroseconds(100);

  // Discard first ADC reading after switching
  analogRead(ADC_PIN);

  delayMicroseconds(20);

  // Actual reading
  return analogRead(ADC_PIN);
}


// ============================================================
// SETUP
// ============================================================

void setup()
{
  Serial.begin(115200);

  // Row MUX pins
  pinMode(R_S0, OUTPUT);
  pinMode(R_S1, OUTPUT);
  pinMode(R_S2, OUTPUT);
  pinMode(R_S3, OUTPUT);

  // Column MUX pins
  pinMode(C_S0, OUTPUT);
  pinMode(C_S1, OUTPUT);
  pinMode(C_S2, OUTPUT);
  pinMode(C_S3, OUTPUT);

  // ADC
  pinMode(ADC_PIN, INPUT);

  // ESP32 ADC = 12 bit
  analogReadResolution(12);

  // GPIO34 is ADC1
  // 11 dB attenuation allows measurement over the
  // useful higher-voltage range of the ESP32 ADC.
  analogSetPinAttenuation(ADC_PIN, ADC_11db);

  // Initial state
  selectRow(0);
  selectColumn(0);

  delay(500);

  Serial.println("ESP32 O-MAT 7x14 READY");
}


// ============================================================
// MAIN LOOP
// ============================================================

void loop()
{
  // Scan all 98 points

  for (uint8_t r = 0; r < N_ROWS; r++)
  {
    for (uint8_t c = 0; c < N_COLS; c++)
    {
      int value = readSensor(r, c);

      Serial.print(value);

      // Comma between readings
      if (!(r == N_ROWS - 1 && c == N_COLS - 1))
      {
        Serial.print(',');
      }
    }
  }

  // End of one complete 7x14 frame
  Serial.println();

  // Small delay before next frame
  delay(10);
}