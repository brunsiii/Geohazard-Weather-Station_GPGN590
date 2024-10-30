#include <Wire.h>
#include <TinyGPS++.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

// GPS and sensor instances
TinyGPSPlus gps;
Adafruit_BME680 bme; // I2C

const int magnetometerAddress = 0x1E;  // Magnetometer I2C address
unsigned long lastPrintTime = 0;
bool headerSent = false;  // Track if the header has been sent

void setup() {
  Serial.begin(9600);  // Initialize serial communication with PC and XBee
  Serial1.begin(9600); // Start GPS communication on Serial1 (pins 18/19)
  Wire.begin();        // Start I2C communication for the magnetometer

  Serial.println("Initializing BN-880 GPS + HMC5883L Magnetometer + BME680...");

  // Initialize Magnetometer (HMC5883L specific setup)
  Wire.beginTransmission(magnetometerAddress);
  Wire.write(0x00);    // Configuration Register A
  Wire.write(0x70);    // 8-average, 15 Hz default, normal measurement
  Wire.endTransmission();

  Wire.beginTransmission(magnetometerAddress);
  Wire.write(0x01);    // Configuration Register B
  Wire.write(0xA0);    // Gain = 5
  Wire.endTransmission();

  Wire.beginTransmission(magnetometerAddress);
  Wire.write(0x02);    // Mode Register
  Wire.write(0x00);    // Continuous measurement mode
  byte error = Wire.endTransmission();

  if (error == 0) {
    Serial.println("HMC5883L Magnetometer initialized successfully!");
  } else {
    Serial.print("ERROR: Magnetometer initialization failed. I2C Error Code: ");
    Serial.println(error);
  }

  // Initialize BME680 sensor
  if (!bme.begin()) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1);
  }
  
  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320°C for 150 ms

  // 1-minute delay before starting transmission
  Serial.println("Waiting for 1 minute before transmission...");
  delay(60000);  // Wait for 60 seconds
}

void readMagnetometer(float &magX, float &magY, float &magZ) {
  Wire.beginTransmission(magnetometerAddress);
  Wire.write(0x03);  // Starting register for data output
  Wire.endTransmission();

  Wire.requestFrom(magnetometerAddress, 6);  // Request 6 bytes (X, Z, Y)

  if (Wire.available() == 6) {
    int16_t x = Wire.read() << 8 | Wire.read();  // X-axis data
    int16_t z = Wire.read() << 8 | Wire.read();  // Z-axis data
    int16_t y = Wire.read() << 8 | Wire.read();  // Y-axis data

    // Convert raw data to microteslas (µT) based on gain setting (0.92 µT/LSB)
    magX = (float)x * 0.92;
    magY = (float)y * 0.92;
    magZ = (float)z * 0.92;
  } else {
    Serial.println("WARNING: Magnetometer data not available.");
  }
}

void loop() {
  // Parse GPS data from Serial1 (connected to GPS module)
  while (Serial1.available() > 0) {
    gps.encode(Serial1.read());
  }

  // Check if 1/2 second has passed
  if (millis() - lastPrintTime >= 500) {
    lastPrintTime = millis();

    // Send header once
    if (!headerSent) {
      Serial.println("Latitude,Longitude,Time,Magnetometer_X(µT),Magnetometer_Y(µT),Magnetometer_Z(µT),Temperature,Humidity,Pressure,Gas Resistance");
      headerSent = true;
    }

    // Read Magnetometer data
    float magX = 0, magY = 0, magZ = 0;
    readMagnetometer(magX, magY, magZ);

    // Read BME680 data
    if (!bme.performReading()) {
      Serial.println("Failed to perform reading from BME680 :(");
      return;
    }

    // Create a string to store the CSV-formatted data
    String dataString = "";

    // Add GPS data if available
    if (gps.location.isValid()) {
      dataString += String(gps.location.lat(), 6) + ",";  // Latitude
      dataString += String(gps.location.lng(), 6) + ",";  // Longitude
    } else {
      dataString += ",";  // Leave empty for Latitude
      dataString += ",";  // Leave empty for Longitude
    }

    // Add time if available
    if (gps.time.isValid()) {
      dataString += String(gps.time.hour()) + ":" + String(gps.time.minute()) + ":" + String(gps.time.second()) + ",";  // Time
    } else {
      dataString += ",";  // Leave empty for Time
    }

    // Add Magnetometer data
    dataString += String(magX) + ",";  // Magnetometer X
    dataString += String(magY) + ",";  // Magnetometer Y
    dataString += String(magZ) + ",";  // Magnetometer Z

    // Add BME680 data
    dataString += String(bme.temperature, 1) + ",";     // Temperature
    dataString += String(bme.humidity, 1) + ",";        // Humidity
    dataString += String(bme.pressure / 100.0, 1) + ","; // Pressure in hPa
    dataString += String(bme.gas_resistance);            // Gas Resistance

    // Send the data to the XBee and Serial Monitor
    Serial.println(dataString);
  }
  
  delay(500);  // Delay between loops (0.5 second)
}

