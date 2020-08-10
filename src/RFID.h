/*
  RFID.h - Library for reading the Parallax RFID Card Reader Serial.
  Created by Isaac Lloyd, Jun 20, 2019.
  Last updated by Isaac Lloyd Aug 9, 2020
*/

#ifndef RFID_h
#define RFID_h

#define SW_SERIAL_OVERIDE // change later

#include "Arduino.h"
#if defined(__AVR__) || defined(ESP8266) || defined(SW_SERIAL_OVERIDE)
#include <SoftwareSerial.h>
#else
#error Cannot use software serial on current board
#endif

typedef void (*new_tag_callback_t) (String newTag);

class RFID {
  public:

	RFID(SoftwareSerial *swSerial, int enablePin);

    void begin();
    void enable();
    void disable();
    bool read(String &ReadTagString);
	bool read();

	void setNewTagCallback(new_tag_callback_t fp);

  private:

	String _currentTag, _prevTag;

	String getTag();

	SoftwareSerial *RFIDReader;

    int _enablePin;
    bool _on = false;

	new_tag_callback_t _newtag_cb;
};

#endif