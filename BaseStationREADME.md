# Base Station Design and Construction
The base station is designed to receive transmitted data and store them on an SD card.
## Hardware Requirements
- Arduino Mega 2560 (2)
- XBee Pro S3B
-     https://www.digi.com/products/embedded-systems/digi-xbee/rf-modules/sub-1-ghz-rf-modules/xbee-pro-xsc
- XBee Shield V2 For Arduino
-     https://www.tinyosshop.com/Xbee%20Shield
- Male-to-male jumper cables (2)
- Ethernet/SD Card Shield
-     https://www.amazon.com/Ethernet-Shield-Network-Expansion-Arduino/dp/B00AXVX5D0/ref=asc_df_B00AXVX5D0?mcid=faca58dcbf3638ecb3e29d4d6658678a&hvocijid=12145263960679792428-B00AXVX5D0-&hvexpln=73&tag=hyprod-20&linkCode=df0&hvadid=721245378154&hvpos=&hvnetw=g&hvrand=12145263960679792428&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9028824&hvtargid=pla-2281435178338&psc=1
- MicroSD Card
## Construction Instructions
1. Stack XBee Shield V2 for Arduino on top of the first Arduino Mega 2560 - this is the Receiving Arduino.
2. Place intialized Base XBee Pro S3B into Base XBee Shield. For instructions on XBee initialization see XBeeREADME.md.
3. Stack Ethernet/SD Card Shield on top of Arduino Mega 2560 - this is the Saving Arduino.
4. Connect pins D18 and D19 of Receiving Arduino to pins D19 and D18 of Saving Arduino. Connecting these respective RX and TX pins establishes the Serial1 connection referenced in the BaseStation1.ino and SavingBaseStation.ino codes.
5. Insert MicroSD card into Ethernet/SD Card Shield.
## Uploading Code
1. Plug both Arduinos into a computer via USB.
2. Compile and upload BaseStation1.ino to Receviing Arduino. Ensure that the MCU-PC switch is set to PC on XBee Shield.
3. Compile and upload SavingBaseStation.ino to Saving Arduino.
## Communicating with Rover and Saving Data
1. Once the Rover has been properly initialized, flip PC to MCU on XBee Shield. See RoverStationREADME.md for instructions on how to construct and intialize the Rover Station.
2. To run independently, unplug Arduinos from laptop and power with 9V batteries.
3. Data should flow to Receiving Arduino and be saved to the SD card on the Saving Arduino.
4. Always power down arduinos before inserting or removing the SD card.
