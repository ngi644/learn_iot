#include <M5Stack.h>

//DHT12 Sensor
#include <DHT12.h>

// Ticker
#include <Ticker.h>

DHT12 dht12;
Ticker tickerMeasure;


void setup() {
  
  // Initialize the M5Stack object
  M5.begin();
  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
  M5.Lcd.fillScreen(TFT_BLACK);

  // setup dht12
  dht12.begin();
  displaySensorData();
  tickerMeasure.attach_ms(5000, displaySensorData);

}

void loop() {

}

void displaySensorData(){
  float temp = dht12.readTemperature();
  float humid = dht12.readHumidity();

  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor(0, 20);
  M5.Lcd.printf("Temperature:%2.1f  \r\nHumidity: %2.0f%%", temp, humid);    
}