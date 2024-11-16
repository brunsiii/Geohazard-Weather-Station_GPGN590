# XBee Communication Initialization
## Software Requirements
- XCTU
- Arduino IDE
## Hardware Requirements
- XBee Pro S3B (2)
-     https://www.digi.com/products/embedded-systems/digi-xbee/rf-modules/sub-1-ghz-rf-modules/xbee-pro-xsc
- XBee Grove Dev Board (2)
-     https://www.digi.com/resources/documentation/digidocs/90001942-13/containers/cont_xbee_grove_development_board.htm
- MicroUSB to USB cable for communication with PC
- Arduino Mega 2560
- BN-880 GPS
-     https://www.amazon.com/Geekstory-Navigation-Raspberry-Aircraft-Controller/dp/B078Y6323W?th=1
- XBee Shield V2 For Arduino (2)
-     https://www.tinyosshop.com/Xbee%20Shield
## Setting Base and Rover Pairs in XCTU
1. Plug both XBee Pro S3B into XBee Grove Dev Board and connect Dev Board to computer via USB.
2. Open XCTU software
### Add Radio Devices
1. Open XCTU software
2. If connecting for first time, press the "Add radio module" button
3. Choose Serial/USB port for first XBee
4. Baud Rate = 9600; Data Bits = 8; Parity = None; Stop Bits = 1; Flow Control = None
5. Click "Finish"
6. Repeat steps 1-5 for a second XBee
## Intialize Base Station
1. Click on the first XBee and then click the gear icon to access its settings.
2. Under section title "MAC/PHY" configure the following settings: Network ID = 1001; Broad ast Multi-Transmits = 3; TX Power Level = Highest [4]
3. Under section title "Network" configure the following settings: Routing/Messaging Mode = Indirect Msg Coordinator [1]
4. Under section title "Addressing" configure the following settings: Destination Address High = 0; Destination Address Low = FFFF; Node Identifier = Base
## Initialize Rover Station
1. Click on the second XBee and then click the gear icon to access its settings.
2. Under section title "MAC/PHY" configure the following settings: Network ID = 1001; Broad ast Multi-Transmits = 3; TX Power Level = Highest [4]
3. Under section title "Network" configure the following settings: Routing/Messaging Mode = Indirect Msg Coordinator [1]
4. Under section title "Addressing" configure the following settings: Destination Address High = 0; Destination Address Low = FFFF; Node Identifier = Rover
### Communicating Data
1. Plug in XBee Shield V2 For Arduino to Base Arduino Mega 2560. Repeat for Rover.
2. Unplug Rover XBee S3B from Dev Board and plug into Rover XBee Shield V2 for Arduino. Repeat for Base.
3. Ensure that the PC-MCU switch on the XBee Shield V2 for Arduino board is set to PC for both Shields.
4. Upload gpsmagxbee.ino code to Rover Arduino to send GPS/Magnetometer data to Rover XBee to be communicated to Base.
5. Upload BaseStation1.ino code to Base Arduino to receive GPS/Magnetometer data from Rover XBee.
6. If saving code to SD card, add SD card breakout board to third Arduino. Ensure SD card is inserted.
7. Connect pins D18 and D19 on Rover to pins D19 and D18 on Base respectively.
8. Once code is uploaded and base station arduino wire connections made between Serial1 pins, switch PC to MCU on both XBee Shields. This allows the Magnetometer/GPS data to be transmitted to the Base station.
9. Unplug serial USBs from all three Arduinos. Plug 9V batteries into each Arduino.
10. You can check that data is being received and saved by powering off the saving base station Arduino, unplugging the SD card, and loading onto a laptop. Data should be in a comma separated .TXT file.
