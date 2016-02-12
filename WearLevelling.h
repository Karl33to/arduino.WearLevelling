/*
  WearLevelling.h - Library for EEPROM wear levelling
  Created by Karl Payne, February 10, 21016.
  Released into the public domain.
*/
#ifndef WearLevelling_h
#define WearLevelling_h

#include "Arduino.h"

class WearLevelling
{
	public:
		WearLevelling(uint16_t wearStart, uint16_t wearSize);
		void clear();
		void debug();
		uint8_t read();
		void write(uint8_t newValue);
		bool isFirst();
		bool isLast();
	private:
		uint16_t _wearStart;
		uint16_t _wearSize;
		RingCounter _ringCcounter;
};

#endif