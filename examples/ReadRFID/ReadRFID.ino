#include <RFID.h> // Include the RFID library

#define enablePin 9 // Pin connected to RFID /ENABLE
#define dataPin 8  // Pin connected to RFID SOUT

SoftwareSerial mySerial(dataPin, 1);
RFID rfid(&mySerial, enablePin);

String newTag; // String to hold the tag read from RFID
String prevTag; // Holds the previous tag as not to print it twice

void setup() {
  Serial.begin(112500);
  rfid.begin();
  Serial.println("RFID Library Basic Example");
}

void loop() {
  rfid.read(newTag);  // Read the tag from the RFID. Stores a 10 digit number in the string
  if (newTag != prevTag) {
    Serial.print("\nNew tag: " + newTag);
    prevTag = newTag;
  }
}