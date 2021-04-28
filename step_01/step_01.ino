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

Ticker tickerMeasure;

void displaySensorData(){

  M5.IMU.getAccelData(&accX,&accY,&accZ);
  M5.IMU.getTempData(&temp);

  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(0, 20);
  M5.Lcd.printf(" %5.2f   %5.2f   %5.2f   ", accX, accY, accZ);
  M5.Lcd.setCursor(0, 60);
  M5.Lcd.printf("Temperature : %.2f C", temp);
  
  yield();
  
}

void setup() {
  
  // Initialize the M5Stack object
  M5.begin();
  M5.Power.begin();

  // Initialize IMU
  M5.IMU.Init();

  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
  M5.Lcd.fillScreen(TFT_BLACK);


  tickerMeasure.attach_ms(500, displaySensorData);

}

void loop() {

}
