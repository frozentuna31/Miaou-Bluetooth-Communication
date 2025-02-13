#include <BluetoothSerial.h> // Include the Bluetooth Serial library

BluetoothSerial SerialBT; // Create a Bluetooth Serial object

#define LED_PIN 22 // Define the GPIO pin for the LED

void setup() {
  Serial.begin(115200); // Start the Serial Monitor
  Serial.println("Initializing Bluetooth...");

  // Start Bluetooth with a custom name
  if (!SerialBT.begin("ESP32_TwoWay")) {
    Serial.println("Bluetooth initialization failed!");
    while (1); // Halt on failure
  }
  Serial.println("Bluetooth initialized successfully. Device is now discoverable.");

  // Initialize the LED pin
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // Ensure LED is OFF initially
}

void loop() {
  // Send a periodic status message
  static unsigned long lastMessageTime = 0;
  if (millis() - lastMessageTime >= 2000) { // Send every 2 seconds
    SerialBT.println("ESP32 is ready. Send commands like 'LED ON' or 'LED OFF'.");
    lastMessageTime = millis();
  }

  // Check for incoming Bluetooth messages
  if (SerialBT.available()) {
    String command = SerialBT.readString(); // Read the received command
    command.trim(); // Remove any leading/trailing whitespace or newline characters
    Serial.println("Raw command received: [" + command + "]");

    // Process the received command
    if (command == "LED ON") {
      digitalWrite(LED_PIN, HIGH); // Turn the LED ON
      SerialBT.println("LED is now ON.");
      Serial.println("LED turned ON.");
    } else if (command == "LED OFF") {
      digitalWrite(LED_PIN, LOW); // Turn the LED OFF
      SerialBT.println("LED is now OFF.");
      Serial.println("LED turned OFF.");
    } else {
      SerialBT.println("Unknown command: " + command);
      Serial.println("Unknown command received.");
    }
  }
}
