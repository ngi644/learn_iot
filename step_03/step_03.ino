#define M5STACK_MPU6886 
// #define M5STACK_MPU9250 
// #define M5STACK_MPU6050
// #define M5STACK_200Q

#include <M5Stack.h>

float accX = 0.0F;
float accY = 0.0F;
float accZ = 0.0F;
float temp = 0.0F;


// Ticker
#include <Ticker.h>

// WiFi
#include <WiFi.h>
#include <time.h>

// wifi config
#define WIFI_SSID "SSID"    
#define WIFI_PASSWORD "WIFI PASSWORD"

Ticker tickerMeasure;

#include "FirebaseESP32.h"
#define FIREBASE_HOST "xxxxx.firebaseio.com"
#define FIREBASE_AUTH "auth-key"

FirebaseData firebaseData;
FirebaseJson fb_json;

String station_name = "station_name";
String lastTimestamp;
bool sensorUpdated = false;


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


void displaySensorData(){

  M5.IMU.getAccelData(&accX,&accY,&accZ);
  M5.IMU.getTempData(&temp);

  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(0, 20);
  M5.Lcd.printf(" %5.2f   %5.2f   %5.2f   ", accX, accY, accZ);
  M5.Lcd.setCursor(0, 60);
  M5.Lcd.printf("Temperature : %.2f C", temp);
  
  // update timestamp
  lastTimestamp = getTimestamp();
  sensorUpdated = true;
  
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
  fb_json.set("temp", temp);
  fb_json.set("acc_x", accX);
  fb_json.set("acc_y", accY);
  fb_json.set("acc_z", accZ);
  fb_json.set("timestamp", lastTimestamp);
  Firebase.pushJSON(firebaseData, "/stations/" + station_name, fb_json);

}


void setup() {

  // Initialize the M5Stack object
  M5.begin();
  M5.Power.begin();
  
  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
  M5.Lcd.fillScreen(TFT_BLACK);

  //Wifi
  setupWiFi();

  // setup firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  // Initialize IMU
  M5.IMU.Init();
  tickerMeasure.attach_ms(500, displaySensorData);

}

void loop() {

  if (sensorUpdated) {
    publishData();
  }

}
