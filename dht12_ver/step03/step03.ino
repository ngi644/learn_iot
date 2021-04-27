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

#include "FirebaseESP32.h"
#include <ArduinoJson.h>
#define FIREBASE_HOST "xxxxx.firebaseio.com"
#define FIREBASE_AUTH "auth-key"

FirebaseData firebaseData;
DynamicJsonBuffer jsonBuffer;

String station_name = "station_name";
float lastTemp;
float lastHumid;
String lastTimestamp;
bool sensorUpdated = false;

void setup() {

  // Initialize the M5Stack object
  M5.begin();
  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
  M5.Lcd.fillScreen(TFT_BLACK);

  //Wifi
  setupWiFi();
  
  // setup firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  // setup dht12
  dht12.begin();
  displaySensorData();
  tickerMeasure.attach_ms(5000, displaySensorData);

}

void loop() {
  
  if (sensorUpdated) {
    publishData();
  }

}

void displaySensorData(){
  lastTemp = dht12.readTemperature();
  lastHumid = dht12.readHumidity();

  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor(0, 20);
  M5.Lcd.printf("Temperature:%2.1f  \r\nHumidity: %2.0f%%", lastTemp, lastHumid);
    
  // update timestamp
  lastTimestamp = getTimestamp();
  sensorUpdated = true;
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

String getTimestamp(){
  struct tm timeinfo;
  char timestamp[20];
  getLocalTime(&timeinfo);
  sprintf(timestamp, "%04d/%02d/%02d %02d:%02d:%02d",
          timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday,
          timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
  yield();
  return (String)timestamp;
}

void publishData(){
  // reset flag
  sensorUpdated = false;

  // push data to firebase
  JsonObject& stationdata = jsonBuffer.createObject();
  stationdata["temp"] = lastTemp;
  stationdata["humid"] = lastHumid;
  stationdata["timestamp"] = lastTimestamp;
  String jsonStr = "";
  stationdata.printTo(jsonStr);
  Firebase.pushJSON(firebaseData, "/stations/" + station_name, jsonStr);

}
