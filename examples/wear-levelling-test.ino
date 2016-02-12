#include <EEPROM.h>
#include <RingCounter.h>
#include <WearLevelling.h>

void setup() {

  Serial.begin(9600);
  delay(10);

  WearLevelling w_counter(0, 10);

  Serial.println("clear");
  w_counter.clear();

  w_counter.debug();

  // increment the counter once to test the isFirst() method
  Serial.println("increment 1");
  w_counter.write(1);

  w_counter.debug();

  if (w_counter.isFirst()) {
    Serial.println("first");
  }
  if (w_counter.isLast()) {
    Serial.println("last");
  }

  Serial.println("increment to 6");
  // populate with some data
  for (uint8_t i = 2; i <= 6; i++) {
    w_counter.write(i);
    delay(10);
  }

  w_counter.debug();

  Serial.println("increment to 12");
  // populate with more data so that it wraps around to the beginning
  for (uint8_t i = 7; i <= 12; i++) {
    w_counter.write(i);
    delay(10);
  }

  w_counter.debug();

  Serial.println("increment to 20");
  // increment the counter a few more times to test the isLast() method
  for (uint8_t i = 13; i <= 20; i++) {
    w_counter.write(i);
    delay(10);
  }

  w_counter.debug();

  if (w_counter.isFirst()) {
    Serial.println("first");
  }
  if (w_counter.isLast()) {
    Serial.println("last");
  }

}
void loop() { }
