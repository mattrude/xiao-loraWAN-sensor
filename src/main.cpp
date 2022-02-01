#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_FeatherOLED.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

Adafruit_BME680 bme;
Adafruit_FeatherOLED oled = Adafruit_FeatherOLED();

void setup() {
  oled.init();
  if (!bme.begin()) { while (1); }
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150);
}

void loop() {
  unsigned long endTime = bme.beginReading();
  if (endTime == 0) { return; }
  if (!bme.endReading()) { return; }
  oled.clearDisplay();
  oled.setCursor(0,0);
  oled.print(F("Temperature: "));
  oled.print((bme.temperature*1.8)+32);
  oled.println(F("f"));
  oled.print(F("Humidity:    "));
  oled.print(bme.humidity);
  oled.println(F("%"));
  oled.print(F("Pressure:   "));
  oled.print(bme.pressure / 100.0);
  oled.println(F("hPa"));
  oled.print(F("Gas:       "));
  oled.print(bme.gas_resistance / 1000.0);
  oled.println(F("KOhms"));
  oled.display();
  delay(15000);
}