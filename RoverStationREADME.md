# Rover Station Design and Construction
The rover station is designed to measure GPS, Magnetometer, temperature, humidity, and pressure data and then compile and transmit all data to base station via XBee.
## Hardware Requirements
- Arduino Mega 2560
-     https://store.arduino.cc/products/arduino-mega-2560-rev3
- XBee Pro S3B
-     https://www.digi.com/products/embedded-systems/digi-xbee/rf-modules/sub-1-ghz-rf-modules/xbee-pro-xsc
- XBee Shield V2 For Arduino
-     https://www.tinyosshop.com/Xbee%20Shield
- BN-880 GPS
-     https://www.amazon.com/Geekstory-Navigation-Raspberry-Aircraft-Controller/dp/B078Y6323W?th=1
- BME 688 Temperature/Pressure/Humidity Sensor
-     https://www.adafruit.com/product/5046

## Construction Instructions
1. Stack XBee Shield V2 for Arduino on top of the Arduino Mega 2560 - this is the Transmitting Arduino.
2. Place intialized Rover XBee Pro S3B into Rover XBee Shield. For instructions on XBee initialization see XBeeREADME.md.
3. Connect GPS Magnetometer and BME 688 to Transmitting Arduino. The GPS Magnetometer connects directly to the RX1 (pin 19) and TX1 (pin 18) pins on the Arduino, and to the 5v and GND pins on the XBee Shield. The BME 688 connects to the 3.5V and GND as well as the SCA adn SCL pins on the Xbee Shield. The RX, TX, SCA, and SCL pins are for transmitting data from the sensor to the base station.
## Uploading Code
1. Plug Arduino into a computer via USB.
2. Compile and upload gpsmagtemp.ino to Transmitting Arduino. Ensure that the MCU-PC switch is set to PC on XBee Shield.
## Communicating with Base
1. Once the Rover has been properly initialized, flip PC to MCU on XBee Shield. See BaseStationREADME.md for instructions on how to construct and intialize the Base Station.
2. To run independently, unplug Arduino from laptop and power with a 9V battery.
