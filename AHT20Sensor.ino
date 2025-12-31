#include <Arduino.h>
#include "AHTSensorManager.h"

AHTSensorManager sensor;    //"quản lý cảm biến"

void setup() {
    Serial.begin(115200);   // Khởi tạo Serial

    sensor.begin(); // Khởi tạo cảm biến
}

void loop() {
  sensor.update();
  static unsigned long printTimer = 0;
    if (millis() - printTimer > 5000) {
        Serial.printf("Temp: %.2f C | Hum: %.2f %%\n", 
                      sensor.getTemp(), 
                      sensor.getHumi());
        printTimer = millis();
    }
}