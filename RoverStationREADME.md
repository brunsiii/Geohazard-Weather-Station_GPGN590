# Base Station Design and Construction
The rover station is designed to measure GPS, Magnetometer, temperature, humidity, and pressure data and then compile and transmit all data and store them on an SD card.
## Hardware Requirements
- Arduino Mega 2560
- XBee Pro S3B
-     https://www.digi.com/products/embedded-systems/digi-xbee/rf-modules/sub-1-ghz-rf-modules/xbee-pro-xsc
- XBee Shield V2 For Arduino
-     https://www.tinyosshop.com/Xbee%20Shield
- BN-880 GPS
-     https://www.amazon.com/Geekstory-Navigation-Raspberry-Aircraft-Controller/dp/B078Y6323W?th=1
- BME 886 Temperature/Pressure/Humidity Sensor

## Construction Instructions
1. Stack XBee Shield V2 for Arduino on top of the Arduino Mega 2560 - this is the Transmitting Arduino.
2. Place intialized Rover XBee Pro S3B into Rover XBee Shield. For instructions on XBee initialization see XBeeREADME.md.
3. Connect GPS Magnetometer and BME 886 to Arduino according to pinout diagram.
4. Connect pins D18 and D19 of Receiving Arduino to pins D19 and D18 of Saving Arduino. Connecting these respective RX and TX pins establishes the Serial1 connection referenced in the BaseStation1.ino and SavingBaseStation.ino codes.
5. Insert MicroSD card into Ethernet/SD Card Shield.
## Uploading Code
1. Plug Arduino into a computer via USB.
2. Compile and upload gpsmagtemp.ino to Transmitting Arduino. Ensure that the MCU-PC switch is set to PC on XBee Shield.
## Communicating with Base
1. Once the Rover has been properly initialized, flip PC to MCU on XBee Shield. See BaseStationREADME.md for instructions on how to construct and intialize the Base Station.
2. To run independently, unplug Arduino from laptop and power with 9V batteries.
