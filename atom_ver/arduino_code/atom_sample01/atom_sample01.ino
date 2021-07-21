#include <M5Atom.h>

// 加速度センサ
#define M5STACK_MPU6886

float accX = 0.0F;
float accY = 0.0F;
float accZ = 0.0F;

// Ticker
#include <Ticker.h>

Ticker tickerMeasure;


void displaySensorData(){

  M5.IMU.getAccelData(&accX,&accY,&accZ);
  Serial.print(accX);
  Serial.print(",");
  Serial.print(accY);
  Serial.print(",");
  Serial.println(accZ);
  yield();
}


void setup() {
  // Initialize the M5Stack object
  M5.begin(true, false, true);

  // Initialize IMU
  M5.IMU.Init();

  tickerMeasure.attach_ms(50, displaySensorData);

}

void loop() {

}
