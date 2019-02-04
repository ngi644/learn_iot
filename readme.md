# ArduinoとFirebaseではじめる観測ステーション


Arduinoとfirebase hosting用のサンプルコードです．


## 利用ハードおよびサービス

- M5Stack
  - https://www.m5stack.com/
  - https://github.com/m5stack/M5Stack
- Firebase
  - https://firebase.google.com/


## IDE

Arduino IDEのほかに，Visual Studio Codeをインストールしておくことを勧めます．

- Arduino IDE
  - https://www.arduino.cc/en/Main/Software
- Visual Studio code
  - https://code.visualstudio.com/


## M5Stackの環境構築

Arduino IDEでM5Stackを利用するための環境構築を行います．

- [M5Stack環境セットアップ(windows)](https://docs.m5stack.com/#/en/quick_start/m5core/m5stack_core_get_started_Arduino_Windows?id=step1-download-arduino-esp32-support)
- [M5Stack環境セットアップ(mac)](https://docs.m5stack.com/#/en/quick_start/m5core/m5stack_core_get_started_Arduino_MacOS)

Arduino IDE内の環境設定における追加ボードマネージャに記述するアドレスは以下となる．

- Arduino-ESP32 Support
  - `https://dl.espressif.com/dl/package_esp32_index.json`


## 利用するArduino用ライブラリ


### 温度センサー用ライブラリ

- DHT12
  - https://github.com/RobTillaart/Arduino

### Firebaseとの通信用ライブラリ

- Firebase ESP32
  - https://github.com/mobizt/Firebase-ESP32
- HTTPClientESP32Ex
  - https://github.com/mobizt/HTTPClientESP32Ex
  

## Webページにおいて利用している可視化ライブラリ

### vis.js

[http://visjs.org/](http://visjs.org/) 3D,2Dの可視化を容易に可能とするjavascriptライブラリです．今回は，2dのグラフ機能を利用しています．