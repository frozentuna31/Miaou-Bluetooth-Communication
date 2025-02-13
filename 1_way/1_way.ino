#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

const char* targetMAC = "B4:9D:02:6B:A9:42"; // Replace with your target device's MAC address

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing Bluetooth...");
  
  if (!SerialBT.begin("ESP32_Sender")) {
    Serial.println("Bluetooth initialization failed!");
    while (1);
  }
  Serial.println("Bluetooth initialized.");
  Serial.print("Attempting to connect to device with MAC: ");
  Serial.println(targetMAC);
  
  if (SerialBT.connect(targetMAC)) {
    Serial.println("Connected successfully!");
  } else {
    Serial.println("Connection failed.");
  }
}

void loop() {
  if (SerialBT.connected()) {
    SerialBT.println("Hello from ESP32!");
    Serial.println("Message sent.");
    delay(2000);
  } else {
    Serial.println("Disconnected. Trying to reconnect...");
    SerialBT.connect(targetMAC);
    delay(5000);
  }
}
