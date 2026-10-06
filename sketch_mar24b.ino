#include <LiquidCrystal.h>

// ── LCD (RS, E, D4, D5, D6, D7) ──
// ⚠️ Using YOUR wiring (D5 included)
LiquidCrystal lcd(19, 18, 5, 23, 22, 21);

// ── MQ-2 sensor ──
#define MQ2_PIN 35

// ── Variables ──
float smoothPPM = 0;
float peakPPM = 0;
bool spike = false;

// ── Timing ──
unsigned long lastLCD = 0;

void setup() {
  Serial.begin(115200);

  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);

  lcd.begin(16, 2);
  lcd.print("System Starting");
  delay(2000);
  lcd.clear();
}

void loop() {

  // ── Read sensor ──
  int raw = analogRead(MQ2_PIN);
  Serial.println(raw);

  // Convert to percentage (adjust if needed)
 float ppm = raw / 4.0;   // simple scaling
ppm = constrain(ppm, 0, 100);
  // ── Smooth value ──
  smoothPPM = (0.3 * ppm) + (0.7 * smoothPPM);

  // ── Peak tracking ──
  if (smoothPPM > peakPPM) {
    peakPPM = smoothPPM;
  }

  // ── Spike detection ──
  if (smoothPPM > 75) {
    spike = true;
  } else if (smoothPPM < 50) {
    spike = false;
  }

  // ── SERIAL PLOTTER OUTPUT ──
  Serial.print("Pollution:");
  Serial.print(smoothPPM);
  Serial.print(",");
  Serial.print("Peak:");
  Serial.println(peakPPM);

  // ── LCD UPDATE ──
  if (millis() - lastLCD > 500) {
    lastLCD = millis();

    lcd.setCursor(0, 0);
    lcd.print("PPM:");
    lcd.print((int)smoothPPM);
    lcd.print("%   ");

    lcd.setCursor(0, 1);
    lcd.print("PK:");
    lcd.print((int)peakPPM);
    lcd.print("% ");

    if (spike) {
      lcd.print("HIGH");
    } else {
      lcd.print("SAFE");
    }
  }

  delay(100);
}