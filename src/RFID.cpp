/*
  RFID.cpp - Library for reading the Parallax RFID Card Reader Serial.
  Created by Isaac Lloyd, Jun 20, 2019.
  Last updated by Isaac Lloyd Aug 9, 2020
*/

#include "Arduino.h"
#include "RFID.h"

RFID::RFID(SoftwareSerial *swSerial, int enablePin) {
	_newtag_cb = NULL;
	RFIDReader = NULL;

	_enablePin = enablePin;

	RFIDReader = swSerial; //TX pin is 1 (Not used)
}

void RFID::begin() {
	RFIDReader->begin(2400);
	pinMode(_enablePin, OUTPUT);
    digitalWrite(_enablePin, 1);
    _on = false;
}

void RFID::enable() {
    digitalWrite(_enablePin, 0);
    _on = true;
}

void RFID::disable() {
    digitalWrite(_enablePin, 1);
    _on = true;
}

void RFID::setNewTagCallback(new_tag_callback_t fp) {
	_newtag_cb = fp;
}

bool RFID::read() {
	if (!_on) { return false; }
	read(_currentTag);
	if (_currentTag != _prevTag) {
		_newtag_cb(_currentTag);
		_prevTag = _currentTag;
		return true;
	}
	return false;
}

bool RFID::read(String &ReadTagString) {
    if (!_on) { return false; }
	ReadTagString = getTag();
    return true;
}

String RFID::getTag() {
	int bytesread = 0;
  	int  val = 0; 
  	char code[10];
  	String TagCode = "";

  	if(RFIDReader->available() > 0) {
        if((val = RFIDReader->read()) == 10) {
            bytesread = 0;
            while(bytesread<10) {
                if(RFIDReader->available() > 0) {
                    val = RFIDReader->read();
                    if((val == 10)||(val == 13)) {
                        break;
                    }
                    code[bytesread] = val;
                    bytesread++;
                }
            }
            if(bytesread == 10) {
                for(int x=0;x<10;x++) {
                    TagCode += code[x];
                }
                while(RFIDReader->available() > 0) {
                    RFIDReader->read();
                }
            }
            bytesread = 0;
        }
    }
	return TagCode;
}