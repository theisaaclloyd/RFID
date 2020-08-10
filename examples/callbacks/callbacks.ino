#include <RFID.h> // Include the RFID library

#define enablePin 9 // Pin connected to RFID /ENABLE
#define dataPin 8  // Pin connected to RFID SOUT

SoftwareSerial mySerial(dataPin, 1);
RFID rfid(&mySerial, enablePin);

void handleNewTag(String newTag) {
	Serial.print("\nNew tag: " + newTag);
}

void setup() {
  Serial.begin(112500);
  
  rfid.begin();
  rfid.setNewTagCallback(handleNewTag);

  Serial.println("RFID Library Callbacks Example");
}

void loop() {
  rfid.read();  // Constantly read tag for callback
}