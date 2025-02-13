#include <BLEDevice.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

// Your device name
const char* targetName = "A52s Rafi";

// Define LED pins
const int LED1 = 25;  // Far LED
const int LED2 = 26;  // Middle LED
const int LED3 = 27;  // Close LED

// RSSI threshold values (you can adjust these)
const int RSSI_CLOSE = -60;    // Very strong signal (very close)
const int RSSI_MIDDLE = -75;   // Medium signal (medium distance)
const int RSSI_FAR = -90;      // Weak signal (far)

// For signal strength display
const char* getSignalStrength(int rssi) {
    if (rssi >= RSSI_CLOSE) return "Excellent";
    else if (rssi >= RSSI_MIDDLE) return "Good";
    else if (rssi >= RSSI_FAR) return "Fair";
    else return "Poor";
}

void updateLEDs(int rssi) {
    // Turn off all LEDs first
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    delay(50);
    
    // Update LEDs based on RSSI value
    if (rssi >= RSSI_CLOSE) {
        // Close - All LEDs on
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, HIGH);
        digitalWrite(LED3, HIGH);
        Serial.println("Distance: Close (<1m)");
    } 
    else if (rssi >= RSSI_MIDDLE) {
        // Middle - Two LEDs on
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, HIGH);
        Serial.println("Distance: Medium (1-3m)");
    } 
    else if (rssi >= RSSI_FAR) {
        // Far - One LED on
        digitalWrite(LED1, HIGH);
        Serial.println("Distance: Far (>3m)");
    }
    else {
        Serial.println("Distance: Out of range");
    }
}

class TargetDeviceCallback : public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
        if (advertisedDevice.haveName() && String(advertisedDevice.getName().c_str()).equals(targetName)) {
            int rssi = advertisedDevice.getRSSI();
            
            // Print connection status
            Serial.println("\n------------------------");
            Serial.printf("Device: %s\n", targetName);
            Serial.printf("Signal Strength: %s (%d dBm)\n", getSignalStrength(rssi), rssi);
            updateLEDs(rssi);
            Serial.println("------------------------\n");
        }
    }
};

void setup() {
    Serial.begin(115200);
    
    // Initialize LED pins
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    
    // Test LEDs
    Serial.println("\nInitializing...");
    Serial.println("Testing LEDs:");
    digitalWrite(LED1, HIGH);
    delay(500);
    digitalWrite(LED2, HIGH);
    delay(500);
    digitalWrite(LED3, HIGH);
    delay(1000);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    
    // Initialize BLE
    BLEDevice::init("ESP32_Distance");
    
    // Configure scanning
    BLEScan* pBLEScan = BLEDevice::getScan();
    pBLEScan->setAdvertisedDeviceCallbacks(new TargetDeviceCallback());
    pBLEScan->setActiveScan(true);
    pBLEScan->setInterval(50);
    pBLEScan->setWindow(49);
    
    Serial.println("\nDistance Detector Ready");
    Serial.printf("Monitoring device: %s\n", targetName);
    Serial.println("\nSignal Strength Ranges:");
    Serial.println("Excellent: > -60 dBm (Close)");
    Serial.println("Good:      -75 to -60 dBm (Medium)");
    Serial.println("Fair:      -90 to -75 dBm (Far)");
    Serial.println("Poor:      < -90 dBm (Out of range)");
    Serial.println("\nStarting scan...");
}

void loop() {
    BLEScan* pBLEScan = BLEDevice::getScan();
    pBLEScan->start(3, false);
    pBLEScan->clearResults();
    delay(100);
}
