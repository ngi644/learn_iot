#include <M5Atom.h>
#include <FastLED.h>
#include <Wire.h>
#include <SPI.h>
#include <SparkFunBME280.h>
#include <Ticker.h>

// Timer event
Ticker tickerBME280;

// BME280
BME280 bme;
BME280_SensorMeasurements measurements;


void displayBME280SensorData() {
  bme.readAllMeasurements(&measurements); 
  Serial.println("Humidity,Pressure,BME-Temp");
  Serial.print(measurements.humidity, 0);
  Serial.print(",");
  Serial.print(measurements.pressure/100, 2);
  Serial.print(",");
  Serial.println(measurements.temperature, 2);
  yield();
}


void setup() {
  M5.begin();

  Serial.begin(115200);

  Wire.begin(26,32);

  bme.setI2CAddress(0x76); //address (0x76 or 0x77)
  if (bme.beginI2C() == false) //Begin communication over I2C 
  {
    Serial.println("The sensor did not respond. Please check wiring.");
    while (1); //Freeze
  }

  tickerBME280.attach_ms(1000, displayBME280SensorData);

}


void loop() {

}
