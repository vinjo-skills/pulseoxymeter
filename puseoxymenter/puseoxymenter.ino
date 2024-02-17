#include <Wire.h>
#include <OakOLED.h>
#include <DFRobot_MAX30102.h>
#include "Adafruit_GFX.h" 
#include <Adafruit_SSD1306.h>

OakOLED oled;
DFRobot_MAX30102 particleSensor;

void setup() {
  Serial.begin(9600);
  delay(1500);

  oled.begin();

  while (!particleSensor.begin()) {
    Serial.println("MAX30102 was not found");
    delay(1000);
  }

  particleSensor.sensorConfiguration(50, SAMPLEAVG_4, MODE_MULTILED, SAMPLERATE_100, PULSEWIDTH_411, ADCRANGE_16384);
}

void loop() {
 
  int32_t SPO2;
  int8_t SPO2Valid;
  int32_t heartRate;
  int8_t heartRateValid;

  Serial.println(F("Wait about four seconds"));

  particleSensor.heartrateAndOxygenSaturation(&SPO2, &SPO2Valid, &heartRate, &heartRateValid);

  Serial.print(F("Heart Rate: "));
  Serial.print(heartRate, DEC);
  Serial.print(F(", Valid: "));
  Serial.print(heartRateValid, DEC);
  Serial.print(F("; SPO2: "));
  Serial.print(SPO2, DEC);
  Serial.print(F(", Valid: "));
  Serial.println(SPO2Valid, DEC);

  // Display results on OLED
  oled.clearDisplay();
  oled.setTextSize(2);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0, 0);
  oled.print(F("HR: "));
  oled.print(heartRate);
  oled.setCursor(0, 40);
  oled.print(F("SPO2: "));
  oled.print(SPO2);
  oled.display();

  delay(2000); // Adjust the delay as needed
}
