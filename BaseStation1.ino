// ChatGPT was consulted to genearte and troubleshoot the following code that reads and prints the received Xbee data to the different Serial ports (OpenAI, November 14 Version).
// Setup function
void setup() {
  // Start communication with Serial Monitor (USB)
  Serial.begin(9600);  // Baud rate for USB communication (Serial Monitor)
  Serial1.begin(9600);
  
  // Inform user through Serial Monitor that we are ready to receive data
  Serial.println("XBee Data Receiver");
  Serial.println("Waiting for data...");
}

// Loop function
void loop() {
  // Check if there is data available from the XBee module
  if (Serial.available()) {
    char receivedByte = Serial.read();  // Read a byte from the XBee
    Serial.print(receivedByte);             // Print the received byte to the Serial Monitor
    Serial1.write(receivedByte);
  }

  // Optional: Add a small delay to avoid excessive CPU usage
  delay(5);
}
