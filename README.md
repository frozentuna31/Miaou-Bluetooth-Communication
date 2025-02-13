MIAO & User Phone Connection by BLE
1.	One-way Communication
  
ESP32 is sending messages to my phone wirelessly via Bluetooth. By the second picture, we can see the greetings from ESP32. 

2.	Two-way Communication
   
   
ESP32 is sending messages to my phone, and we can command the LED to turn it ON or OFF. By the pictures, if we give the LED ON or LED OFF command, the light will turn it according to the order given and ESP will also reply the current condition after the action. 

3.	Localization 
 
   
Locate the phone using ESP32 Bluetooth LE based on RSSI in dBm for 
1.	Close (-60<dBm) 
2.	Medium (-75<dBm< -60) 
3.	Far (dBm<-75)
It works for all positions outside of the video. You need at least 3 ESP32's to determine accurate location.
