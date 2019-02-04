#include <M5Stack.h>

//DHT12 Sensor
#include <DHT12.h>

DHT12 dht12;

void setup() {
  
  // Initialize the M5Stack object
  M5.begin();
  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
  M5.Lcd.fillScreen(TFT_BLACK);

  // setup dht12
  dht12.begin();
  displaySensorData();

}

void loop() {

}

void displaySensorData(){
  temp = dht12.readTemperature();
  humid = dht12.readHumidity();

  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor(0, 20);
  M5.Lcd.printf("Temperature:%2.1f  \r\nHumidity: %2.0f%%", temp, humid);

  yeild()
}