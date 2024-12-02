// This code was adpated from Arduino Workshop, "Project 22 - Writing Data to the Memory Card" such that the communicated data is saved to an SD card.
// ChatGPT was consulted to troubleshoot the saving mechanisms of the following code (OpenAI, 2024, November 14 Version).
// Project 22 - Writing Data to the Memory Card
#include <SD.h>
int b = 0;
void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.println("Initializing SD card...");
  pinMode(4, OUTPUT);
  // check that the memory card exists and is usable
  if (!SD.begin(4))
  {
    Serial.println("Card failed, or not present");
    // stop sketch
    return;
  }
  Serial.println("memory card is ready");
}
void loop()
{
    // Check if there is data available from the XBee (connected to Serial)
  if (Serial1.available()) {
    char receivedByte = Serial1.read();  // Read a byte from the XBee
    
    // Print the received byte to the Serial Monitor (USB)
    Serial.print("Received Byte: ");
    Serial.println(receivedByte);
  
  // create the file for writing
  File dataFile = SD.open("SAVE.TXT", FILE_WRITE);
  // if the file is ready, write to it:
  if (dataFile)
  {
    dataFile.print(receivedByte);
    dataFile.close(); // close the file once the system has finished with it
                      // (mandatory)
  }
  // if the file isn't ready, show an error:
  else
  {
    Serial.println("error opening DATA.TXT");
  }
  }
  delay(5);
}

// References
// 
