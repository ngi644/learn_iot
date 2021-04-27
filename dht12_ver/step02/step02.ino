#include <M5Stack.h>

//DHT12 Sensor
#include <DHT12.h>

// Ticker
#include <Ticker.h>

// WiFi
#include <WiFi.h>
#include <time.h>

// wifi config
#define WIFI_SSID "SSID"    
#define WIFI_PASSWORD "WIFI PASSWORD"

DHT12 dht12;
Ticker tickerMeasure;


void setup() {

  // Initialize the M5Stack object
  M5.begin();
  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
  M5.Lcd.fillScreen(TFT_BLACK);

  //Wifi
  setupWiFi();
  
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

void setupWiFi(){
  // connect wifi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);  
  while (WiFi.status() != WL_CONNECTED) {
    M5.Lcd.printf(".");
    delay(100);
    }
  M5.Lcd.fillScreen(TFT_BLACK);
  M5.Lcd.setCursor(0, 220);
  M5.Lcd.printf("SSID: ");
  M5.Lcd.println(WIFI_SSID);
  M5.Lcd.printf("IP address: ");
  M5.Lcd.println(WiFi.localIP());
  // sync Time
  configTime( 3600L * 9, 0, "ntp.nict.jp", "ntp.jst.mfeed.ad.jp");  
}