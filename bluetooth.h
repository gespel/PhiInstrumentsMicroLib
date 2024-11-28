#pragma once
#include "Arduino.h"
#include "BluetoothSerial.h"

class Bluetooth {
public:
    Bluetooth();
    String recv();
private:
    BluetoothSerial SerialBT;
};

Bluetooth::Bluetooth() {
    SerialBT.begin("ESP32test");
}

String Bluetooth::recv() {
    if(SerialBT.available()) {
        Serial.write(SerialBT.read());
    }
}