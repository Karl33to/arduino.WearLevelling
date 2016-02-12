#include "Arduino.h"
#include "EEPROM.h"
#include "RingCounter.h"
#include "WearLevelling.h"

// the memory location at which the ring counter starts [0-65535]
uint16_t _wearStart;

// the number of bytes to use for the counter [0-65535]
// the storage will also use this number of bytes
uint16_t _wearSize;

WearLevelling::WearLevelling(uint16_t wearStart, uint16_t wearSize) : _ringCcounter(wearStart, wearSize)
{
	_wearStart = wearStart;
	_wearSize = wearSize;
	RingCounter _ringCcounter(wearStart, wearSize);
}

// clear any previously used EEPROM
void WearLevelling::clear() {
	_ringCcounter.clear();
	const uint16_t counterStart = _wearStart + _wearSize;
	const uint16_t counterEnd = (_wearStart + (_wearSize * 2)) - 1;
	for (uint16_t i = counterStart; i <= counterEnd; i++) {
		EEPROM.write(i, 0);
	}
}

// prints the EEPROM memory to Serial
void WearLevelling::debug() {
	_ringCcounter.debug();
	Serial.print("WearLevelling::debug	[");
	const uint16_t counterStart = _wearStart + _wearSize;
	const uint16_t counterEnd = (_wearStart + (_wearSize * 2)) - 1;
	for (uint16_t i = counterStart; i <= counterEnd; i++) {
		Serial.print(EEPROM.read(i));
		Serial.print(",");
	}
	Serial.println("]");
}

// read the last byte of data that was written to the EEPROM
uint8_t WearLevelling::read() {
	const uint16_t offset = _ringCcounter.current();
	const uint16_t storagePos = (_wearStart + _wearSize) + offset;
	return EEPROM.read(storagePos);
}

// write a new byte of data to the EEPROM
void WearLevelling::write(uint8_t newValue) {
	const uint16_t next_offset = _ringCcounter.next();
	const uint16_t storagePos = (_wearStart + _wearSize) + next_offset;
	EEPROM.write(storagePos, newValue);
	_ringCcounter.increment();
}

bool WearLevelling::isFirst(){
	uint16_t current_offset = _ringCcounter.current();
	if (current_offset == 0) {
		return true;
	} else {
		return false;
	}
}

bool WearLevelling::isLast(){
	uint16_t current_offset = _ringCcounter.current();
	if (current_offset == (_wearSize -1)) {
		return true;
	} else {
		return false;
	}
}